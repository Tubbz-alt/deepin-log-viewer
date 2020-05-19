/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     AaronZhang <ya.zhang@archermind.com>
 *
 * Maintainer: AaronZhang <ya.zhang@archermind.com>
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

#include "logtableview.h"
#include <QDebug>

DWIDGET_USE_NAMESPACE

LogTableView::LogTableView(QWidget *parent)
    : DTableView(parent)
{
    this->setFocus();
}

void LogTableView::focusInEvent(QFocusEvent *event)
{
    qDebug() << "focus in";
}

void LogTableView::focusOutEvent(QFocusEvent *event)
{
    qDebug() << "focus in";
    //    this->setFocus();
    //    DTableView::focusOutEvent(event);
}
