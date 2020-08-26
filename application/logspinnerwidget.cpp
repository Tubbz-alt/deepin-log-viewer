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

#include "logspinnerwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE

LogSpinnerWidget::LogSpinnerWidget(QWidget *parent)
    : Dtk::Widget::DWidget(parent)
{
    initUI();
}
/**
 * @brief LogSpinnerWidget::initUI  主表加载数据时的spinner
 * 把DSpinner通过弹簧放在布局中间
 */
void LogSpinnerWidget::initUI()
{
    m_spinner = new DSpinner(this);
    m_spinner->setFixedSize(QSize(32, 32));

    //    QHBoxLayout *hh = new QHBoxLayout(this);

    QHBoxLayout *h = new QHBoxLayout(this);
    h->addStretch(1);

    QVBoxLayout *v = new QVBoxLayout(this);
    v->addStretch(1);
    v->addWidget(m_spinner);
    v->addStretch(1);

    h->addLayout(v);
    h->addStretch(1);

    //    hh->addLayout(h);
    this->setLayout(h);
}

void LogSpinnerWidget::spinnerStart()
{
    m_spinner->start();
}

void LogSpinnerWidget::spinnerStop()
{
    m_spinner->stop();
}
