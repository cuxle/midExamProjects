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
#include "networkserver.h"
#include "datamanagerdb.h"

SchoolListTableModel::SchoolListTableModel(QList<School*> &schools, QObject *parent) :
    QSqlTableModel(parent),
    m_schools(schools)
{
    m_columnCount = 4;
}

int SchoolListTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return QSqlTableModel::rowCount(parent);
}

int SchoolListTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return QSqlTableModel::columnCount(parent);
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
//        qDebug() << __func__ << __LINE__ << index.row() << index.column() << QSqlTableModel::data(index, role).toInt();
        return (QSqlTableModel::data(index, Qt::DisplayRole).toInt() == 0) ? Qt::Unchecked : Qt::Checked;
    } else if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0:
        {
            int c = QSqlTableModel::data(index, role).toInt();
//            qDebug() << __func__ << __LINE__ << c;
            return (c == 0) ? QString("未选中") : QString("选中");
        }

        case 1:
            return QSqlTableModel::data(index, role).toString();
        case 2:            
            return QSqlTableModel::data(index, role).toString();
        case 3:
            return (QSqlTableModel::data(index, role).toUInt() == 0) ? "未下载" : "已下载";
        default:
            break;
        }
//        return m_data[index.row()]->at(index.column());
    }
    return QVariant();
}

Qt::ItemFlags SchoolListTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlTableModel::flags(index) & ~Qt::ItemIsEditable;
    if (index.column() == 0) {
        return flags | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable;
    }
    return flags;
}

void SchoolListTableModel::schoolListDataChanged()
{
    updateModel();
}

bool SchoolListTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role) {
    case Qt::CheckStateRole:
        qDebug() << __func__ << role;
        if (index.column() == 0) {
            int checked = data(index, Qt::CheckStateRole).toUInt();
            qDebug() << __func__ << __LINE__ << checked;
            if (checked == (int)Qt::Checked) {
                checked = (int)Qt::Unchecked;
            } else {
                checked = (int)Qt::Checked;
            }

            QModelIndex indexZXDM = createIndex(index.row(), index.column() + 1);
            QVariant zxdm = data(indexZXDM);

            qDebug() << __func__ << __LINE__ << checked;
//            QString zxdm = data();
//            m_schools.at(index.row())->checked = enable;
//            emit dataChanged(index, index);
            DataManagerDb::updateSchoolCheckedStatus(zxdm.toString(), checked);
//            QSqlTableModel::setData(index, enable, role);
//            updateModel();
            this->select();
            QVariant afterEnable = data(index, Qt::CheckStateRole);
            qDebug() << __func__ << __LINE__ << afterEnable;
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
    QModelIndex index = createIndex(0, 0);
    emit dataChanged(index, index);
}
