/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     LZ <zhou.lu@archermind.com>
 *
 * Maintainer: LZ <zhou.lu@archermind.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DISPLAYCONTENT_H
#define DISPLAYCONTENT_H

#include <DApplicationHelper>
#include <DIconButton>
#include <DLabel>
#include <DSpinner>
#include <DTableView>
#include <DTextBrowser>
#include <QStandardItemModel>
#include <QWidget>
#include "filtercontent.h"  //add by Airy
#include "logdetailinfowidget.h"
#include "logfileparser.h"
#include "logiconbutton.h"
#include "logspinnerwidget.h"
#include "logtreeview.h"
#include "structdef.h"



class DisplayContent : public Dtk::Widget::DWidget
{
    Q_OBJECT
    enum LOAD_STATE {
        DATA_LOADING = 0,
        DATA_COMPLETE,
        DATA_LOADING_K,
        DATA_NO_SEARCH_RESULT,
    };
public:
    explicit DisplayContent(QWidget *parent = nullptr);
    ~DisplayContent();

public:

private:
    void initUI();
    void initMap();
    void initTableView();
    void setTableViewData();
    void initConnections();

    void generateJournalFile(int id, int lId);
    void createJournalTable(QList<LOG_MSG_JOURNAL> &list);

    void generateDpkgFile(int id);
    void createDpkgTable(QList<LOG_MSG_DPKG> &list);

    void generateKernFile(int id);
    void createKernTable(QList<LOG_MSG_JOURNAL> &list);

    void generateAppFile(QString path, int id, int lId);
    void createAppTable(QList<LOG_MSG_APPLICATOIN> &list);
    void createApplicationTable(QList<LOG_MSG_APPLICATOIN> &list);

    void createBootTable(QList<LOG_MSG_BOOT> &list);

    void createXorgTable(QList<LOG_MSG_XORG> &list);
    void generateXorgFile(int id);  // add by Airy for peroid

    void createNormalTable(QList<LOG_MSG_NORMAL> &list);  // add by Airy
    void generateNormalFile(int id);                      // add by Airy for peroid

    void insertJournalTable(QList<LOG_MSG_JOURNAL> logList, int start, int end);
    void insertApplicationTable(QList<LOG_MSG_APPLICATOIN> list, int start, int end);
    void insertKernTable(QList<LOG_MSG_JOURNAL> list, int start,
                         int end);  // add by Airy for bug 12263

    QString getAppName(QString filePath);

    bool isAuthProcessAlive();


    //

signals:
    void loadMoreInfo();
    void sigDetailInfo(QModelIndex index, QStandardItemModel *pModel, QString name);

public slots:
    void slot_tableItemClicked(const QModelIndex &index);
    void slot_BtnSelected(int btnId, int lId, QModelIndex idx);
    void slot_appLogs(QString path);

    void slot_logCatelogueClicked(const QModelIndex &index);
    void slot_exportClicked();

    void slot_statusChagned(QString status);

    void slot_dpkgFinished();
    void slot_XorgFinished();
    void slot_bootFinished(QList<LOG_MSG_BOOT> list);
    void slot_kernFinished(QList<LOG_MSG_JOURNAL> list);
    void slot_journalFinished();
    void slot_applicationFinished(QList<LOG_MSG_APPLICATOIN> list);
    void slot_NormalFinished();  // add by Airy

    void slot_vScrollValueChanged(int value);

    void slot_searchResult(QString str);

    void slot_themeChanged(Dtk::Widget::DApplicationHelper::ColorType colorType);

    void slot_getLogtype(int tcbx);  // add by Airy
    void slot_refreshClicked(const QModelIndex &index); //add by Airy for adding refresh
//导出前把当前要导出的当前信息的Qlist转换成QStandardItemModel便于导出
    void parseListToModel(QList<LOG_MSG_DPKG> iList, QStandardItemModel *oPModel);
    void parseListToModel(QList<LOG_MSG_BOOT> iList, QStandardItemModel *oPModel);
    void parseListToModel(QList<LOG_MSG_APPLICATOIN> iList, QStandardItemModel *oPModel);
    void parseListToModel(QList<LOG_MSG_XORG> iList, QStandardItemModel *oPModel);
    void parseListToModel(QList<LOG_MSG_JOURNAL> iList, QStandardItemModel *oPModel);
    void parseListToModel(QList<LOG_MSG_NORMAL> iList, QStandardItemModel *oPModel);
    void setLoadState(LOAD_STATE iState);
private:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    //    Dtk::Widget::DTableView *m_tableView;
    LogTreeView *m_treeView;
    QStandardItemModel *m_pModel;


    logDetailInfoWidget *m_detailWgt {nullptr};
    Dtk::Widget::DLabel *noResultLabel {nullptr};
    QModelIndex m_curListIdx;
    QMap<QString, QString> m_transDict;
    int m_limitTag {0};

    LogSpinnerWidget *m_spinnerWgt;
    LogSpinnerWidget *m_spinnerWgt_K;  // add by Airy

    QString m_curAppLog;
    QString m_currentStatus;

    int m_curBtnId {ALL};
    int m_curLevel {INF};

    LOG_FLAG m_flag {NONE};

    LogFileParser m_logFileParse;
    QList<LOG_MSG_JOURNAL> jList;  // journalctl cmd.
    QList<LOG_MSG_DPKG> dList;     // dpkg.log
    //    QStringList xList;                           // Xorg.0.log
    QList<LOG_MSG_XORG> xList;                   // Xorg.0.log
    QList<LOG_MSG_BOOT> bList, currentBootList;  // boot.log
    QList<LOG_MSG_JOURNAL> kList;                // kern.log
    QList<LOG_MSG_APPLICATOIN> appList;          //~/.cache/deepin/xxx.log(.xxx)
    QList<LOG_MSG_NORMAL> norList;               // add by Airy
    QList<LOG_MSG_NORMAL> nortempList;           // add by Airy
    QString m_iconPrefix = ICONPREFIX;
    QMap<QString, QString> m_icon_name_map;
    QString getIconByname(QString str);
    QString m_currentSearchStr{""};
};

#endif  // DISPLAYCONTENT_H
