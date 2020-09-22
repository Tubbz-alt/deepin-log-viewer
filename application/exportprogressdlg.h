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
#ifndef EXPORTPROGRESSDLG_H
#define EXPORTPROGRESSDLG_H
#include <DDialog>
#include <DProgressBar>
#include <DWidget>
DWIDGET_USE_NAMESPACE

class ExportProgressDlg : public DDialog
{
    Q_OBJECT
public:
    explicit ExportProgressDlg(DWidget *parent = nullptr);

    void setProgressBarRange(int minValue, int maxValue);
    void updateProgressBarValue(int curValue);
signals:
    void sigCloseBtnClicked();
protected:
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

private:
    DProgressBar *m_pExportProgressBar;
};

#endif // EXPORTPROGRESSDLG_H
