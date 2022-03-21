/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#pragma execution_character_set("utf-8")
#include "schoollisttablemodel.h"
#include <QtCore/QVector>
#include <QtCore/QRandomGenerator>
#include <QtCore/QRect>
#include <QtGui/QColor>
#include <QFont>

#include "singleton.h"
#include "networkServer/networkserver.h"

SchoolListTableModel::SchoolListTableModel(QList<School*> &schools, QObject *parent) :
    QAbstractTableModel(parent),
    m_schools(schools)
{
    m_columnCount = 4;
}

int SchoolListTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_schools.count();
}

int SchoolListTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
}

QVariant SchoolListTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole) {
        return (Qt::AlignCenter);
    } else if (role == Qt::FontRole) {
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPixelSize(18);
        return font;
    } else if (role == Qt::TextColorRole) {
        QColor color = Qt::white;
        return QVariant::fromValue(color);
    } else if (role == Qt::CheckStateRole && index.column() == 0) {
        return m_schools.at(index.row())->checked ? Qt::Checked : Qt::Unchecked;
    } else if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
            return m_schools.at(index.row())->checked ? QString("选中") : QString("未选中");
        case 1:
            return m_schools[index.row()]->zxdm;
        case 2:            
            return m_schools[index.row()]->schoolName;
        case 3:
            return m_schools[index.row()]->status == 0 ? "未下载" : "已下载";
        default:
            break;
        }
//        return m_data[index.row()]->at(index.column());
    }
    return QVariant();
}

Qt::ItemFlags SchoolListTableModel::flags(const QModelIndex &index) const
{
    if (index.column() == 0) {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    }
    return QAbstractItemModel::flags(index);
}

void SchoolListTableModel::insertRow(int position, const QModelIndex &parent)
{
    updateModel();
    return;
    if ((position < 0) || (position >= m_schools.size()))
        return;

    beginInsertRows(parent, position, position);
//	XFrameData fd = m_pSendDatas->at(position);
//    fd.clearFrMsgIndex();
//	m_pSendDatas->insert(position, fd);
//    FRCommander::updateFrMsg2Device(fd, m_pro, true);

    endInsertRows();
}

void SchoolListTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

void SchoolListTableModel::schoolListDataChanged()
{
    insertRow(m_schools.size() - 1);
}

bool SchoolListTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role) {
    case Qt::CheckStateRole:
        qDebug() << __func__ << role;
        if (index.column() == 0) {
            bool enable = value.toBool();
            m_schools.at(index.row())->checked = enable;
            emit dataChanged(index, index);
        }
        break;
    default:
        break;
    }
    return true;
}

void SchoolListTableModel::updateModel()
{
    beginResetModel();
    endResetModel();
}
