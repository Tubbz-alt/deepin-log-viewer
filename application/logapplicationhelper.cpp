/*
* Copyright (C) 2019 ~ 2020 UnionTech Software Technology Co.,Ltd
*
* Author:     zyc <zyc@uniontech.com>
* Maintainer:  zyc <zyc@uniontech.com>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "logapplicationhelper.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QLocale>



std::atomic<LogApplicationHelper *> LogApplicationHelper::m_instance;
std::mutex LogApplicationHelper::m_mutex;

/**
 * @brief LogApplicationHelper::LogApplicationHelper 构造函数，获取日志文件路径和应用名称
 * @param parent 父对象
 */
LogApplicationHelper::LogApplicationHelper(QObject *parent)
    : QObject(parent)
    , m_DbusLauncher(new DBbusLauncher(DBbusLauncher::staticInterfaceName(), "/com/deepin/dde/daemon/Launcher", QDBusConnection::sessionBus(), this))
{
    init();
}

/**
 * @brief LogApplicationHelper::init  初始化数据函数
 */
void LogApplicationHelper::init()
{
    m_desktop_files.clear();
    m_log_files.clear();

    m_en_log_map.clear();
    m_en_trans_map.clear();
    m_trans_log_map.clear();

    // get current system language shortname
    m_current_system_language = QLocale::system().name();

    // get desktop & log files
    createDesktopFiles();
    createLogFiles();
}

/**
 * @brief LogApplicationHelper::createDesktopFiles 通过所有符合条件的destop文件获得包名和对应的应用文本
 */
void LogApplicationHelper::createDesktopFiles()
{
    QDBusPendingReply<LauncherItemInfoList> reply   = m_DbusLauncher->GetAllItemInfos();
    if (reply.isError()) {
        qWarning() << "application info from dbus is empty!!";
        qWarning() << reply.error();
        return;
    }

    const LauncherItemInfoList &datas = reply.value();
    QStringList fileInfoListDbus;
    for (const auto &it : datas) {
        qDebug() << "createDesktopFiles" << it.ID << it.Icon << it.Name << it.Path << it.CategoryID << it.TimeInstalled;
        if (it.Path.contains("deepin-") ||  it.Path.contains("dde-")) {
            m_desktop_files.append(it.Path);
        }
    }
    //在该目录下遍历所有desktop文件
    QString path = "/usr/share/applications";
    QDir dir(path);
    if (!dir.exists())
        return;

    QStringList fileInfoList = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    for (QString desktop : fileInfoList) {
        //需要符合以deepin或者dde开头的应用
        if (desktop.contains("deepin-") || desktop.contains("dde-")) {
            //   m_desktop_files.append(desktop);
        }
    }
    qDebug() << "  m_desktop_files.count()" <<    m_desktop_files.count();
    qDebug() << "fileInfoListDbus" <<    fileInfoListDbus.count();
    for (QString var : m_desktop_files) {
        //QString filePath = path + "/" + var;
        QString filePath = var;
        //  qDebug() << "m_desktop_files filePath" << filePath;
        QFile fi(filePath);
        if (!fi.open(QIODevice::ReadOnly))
            continue;

        bool isDeepin = false;
        bool isGeneric = false;
        bool isName = false;

        while (!fi.atEnd()) {
            QString lineStr = fi.readLine();
            lineStr.replace("\n", "");

            if (lineStr.startsWith("GenericName", Qt::CaseInsensitive) && !isGeneric) {
                isGeneric = true;
            }
            if (lineStr.startsWith("Name", Qt::CaseInsensitive) && !isName) {
                isName = true;
            }

            if (!lineStr.contains("X-Deepin-Vendor", Qt::CaseInsensitive)) {
                continue;
            }

            QStringList _x_vendor_list = lineStr.split("=", QString::SkipEmptyParts);
            if (_x_vendor_list.count() != 2) {
                continue;
            }

            QString rval = _x_vendor_list[1];
            if (0 == rval.compare("deepin", Qt::CaseInsensitive)) {
                isDeepin = true;
                break;
            }
        }
        fi.close();
        //转换插入应用包名和应用显示文本到数据结构
        parseField(filePath, var.split(QDir::separator()).last(), isDeepin, isGeneric, isName);
    }
}

/**
 * @brief LogApplicationHelper::createLogFiles 根据找到的符合要求的desktop文件的应用去初始化应用日志文件路径
 */
void LogApplicationHelper::createLogFiles()
{
    QString homePath = QDir::homePath();
    if (homePath.isEmpty()) {
        return;
    }
    QString path = homePath + "/.cache/deepin/";
    QDir appDir(path);
    if (!appDir.exists()) {
        return;
    }

    m_log_files = appDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
//    qDebug() << "m_desktop_files" << m_desktop_files;

    for (auto i = 0; i < m_desktop_files.count(); ++i) {
        QString _name = m_desktop_files[i].split(QDir::separator()).last().section(".", 0, 0);

        for (auto j = 0; j < m_log_files.count(); ++j) {
            //desktop文件名和日志文件名比较，相同则符合条件
            if (_name == m_log_files[j]) {
                QString logPath = path + m_log_files[j];
                m_en_log_map.insert(_name, logPath);
                break;
            }
        }
    }
}

/**
 * @brief LogApplicationHelper::parseField 从desktop文件中提取正确的显示文本
 * @param path desktop文件路径
 * @param name 包名
 * @param isDeepin  是否是deepin应用
 * @param isGeneric 是否有GenericName字段
 * @param isName 是否有Name字段
 */
void LogApplicationHelper::parseField(QString path, QString name, bool isDeepin, bool isGeneric,
                                      bool isName)
{
    Q_UNUSED(isName)
    QFile fi(path);
    if (!fi.open(QIODevice::ReadOnly)) {
        return;
    }
//   qDebug() << "parseField" << "path" << path << "name" << name << "isDeepin" << isDeepin << "isGeneric" << isGeneric << "isName" << isName;
    // insert map at first, en-en, then repalce transName if has name,
    m_en_trans_map.insert(name.section(".", 0, 0), name.section(".", 0, 0));  // desktop name

    while (!fi.atEnd()) {
        QString lineStr = fi.readLine();
        lineStr.replace("\n", "");

        if (isDeepin) {
            // GenericName所对应的当前语言的值=》GenericName无任何语言标记的值=》Name对应语言的值
            // =》Name无任何语言标记的值 =》desktop的名称

            if (isGeneric) {
                if (!lineStr.startsWith("GenericName"))
                    continue;
            } else {
                if (!lineStr.startsWith("Name"))
                    continue;
            }

        } else {
            // Name对应语言的值 =》Name无任何语言标记的值 =》desktop的名称
            if (!lineStr.startsWith("Name"))
                continue;
        }

        QStringList gNameList = lineStr.split("=", QString::SkipEmptyParts);
        if (gNameList.count() != 2)
            continue;

        QString leftStr = gNameList[0];
        QString genericName = gNameList[1];
        //  qDebug() << "leftStr" << leftStr;
        if (leftStr.split("_").count() == 2) {
            // qDebug() << "  if (leftStr.split(_).count() == 2) {" << leftStr << m_current_system_language;
            if (leftStr.contains(m_current_system_language)) {
                //    qDebug() << " if (leftStr.contains(m_current_system_language)) {";
                m_en_trans_map.insert(name.section(".", 0, 0), genericName);
                break;
            }
        } else if (leftStr.contains(m_current_system_language.split("_")[0])) {
            // qDebug() << " if (leftStr.contains(m_current_system_language.split(_)[0])) {";
            m_en_trans_map.insert(name.section(".", 0, 0), genericName);
            break;
        } else if (0 == leftStr.compare("GenericName", Qt::CaseInsensitive) ||
                   0 == leftStr.compare("Name", Qt::CaseInsensitive)) {
            //   qDebug() << " if (0 == leftStr.compare(\"GenericName\", Qt::CaseInsensitive) || 0 == leftStr.compare(\"Name\", Qt::CaseInsensitive)) {";
            // could not find GenericName[...], use GenericName=
            m_en_trans_map.insert(name.section(".", 0, 0), genericName);  // GenericName=xxxx
        }
    }
}

/**
 * @brief LogApplicationHelper::getLogFile 通过日志目录获取日志文件路经
 * @param path 通过日志文件目录
 * @return 日志文件路经
 */
QString LogApplicationHelper::getLogFile(QString path)
{
    QString ret;
    QDir subdir(path);
    if (!subdir.exists())
        return ret;

    QStringList logFiles = subdir.entryList(QDir::NoDotAndDotDot | QDir::Files);

    for (int j = 0; j < logFiles.count(); j++) {
        QString fileName = logFiles.at(j);
        if (!fileName.endsWith(".log"))
            continue;
        ret = QString("%1/%2").arg(path).arg(fileName);
        break;
    }
    return ret;
}

/**
 * @brief LogApplicationHelper::getMap 刷新并返回所有显示文本对应的应用日志路径
 * @return
 */
QMap<QString, QString> LogApplicationHelper::getMap()
{
//     qDebug() << "m_en_log_map" << m_en_log_map;
    // qDebug() << "m_en_trans_map" << m_en_trans_map;
    init();
    QMap<QString, QString>::const_iterator iter = m_en_log_map.constBegin();
    while (iter != m_en_log_map.constEnd()) {
        QString displayName = m_en_trans_map.value(iter.key());
        QString logPath = getLogFile(iter.value());
        m_trans_log_map.insert(displayName, logPath);
        ++iter;
    }
    return m_trans_log_map;
}

/**
 * @brief LogApplicationHelper::transName 从应用包名转换为应用显示文本
 * @param str 应用包名
 * @return 显示文本
 */
QString LogApplicationHelper::transName(QString str)
{
    return m_en_trans_map.value(str);
}
