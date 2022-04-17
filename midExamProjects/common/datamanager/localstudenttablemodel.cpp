#pragma execution_character_set("utf-8")

#include "localstudenttablemodel.h"
#include <QStringLiteral>
#include <QFont>
#include <QColor>

LocalStudentTableModel::LocalStudentTableModel(QObject *parent) :
    QSqlTableModel(parent)
{

}

int LocalStudentTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
//    return m_students.count();
    return QSqlTableModel::rowCount(parent);
}

int LocalStudentTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
//    return m_columnCount;
    return QSqlTableModel::columnCount(parent);
}

QVariant LocalStudentTableModel::data(const QModelIndex &index, int role) const
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
        QModelIndex midStopIndex = createIndex(index.row(), index.column() + 3);
        if ((index.column() == FirstScore && QSqlTableModel::data(midStopIndex).toBool()) ||
                (index.column() == SecondScore && QSqlTableModel::data(midStopIndex).toBool()) ||
                (index.column() == ThirdScore && QSqlTableModel::data(midStopIndex).toBool())) {
            color = Qt::red;
        }
        return QVariant::fromValue(color);
    } else if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case Gender:
        {
            int gender = QSqlTableModel::data(index).toInt();
            if (gender == 1) {
                return QVariant("男");
            } else if (gender == 2) {
                return QVariant("女");
            }
            break;
        }
        case FirstScore:
        {
            QModelIndex indexMidStopFirst = createIndex(index.row(), MidStopFirst);
            bool isMidStop = QSqlTableModel::data(indexMidStopFirst).toBool();
            QVariant variant;
            if (isMidStop) {
                variant = "犯规";
                return variant;
            }
            break;
        }
        case SecondScore:
        {
            QModelIndex indexMidStopFirst = createIndex(index.row(), MidStopSecond);
            bool isMidStop = QSqlTableModel::data(indexMidStopFirst).toBool();
            QVariant variant;
            if (isMidStop) {
                variant = "犯规";
                return variant;
            }
            break;
        }
        case ThirdScore:
        {
            QModelIndex indexMidStopFirst = createIndex(index.row(), MidStopThird);
            bool isMidStop = QSqlTableModel::data(indexMidStopFirst).toBool();
            QVariant variant;
            if (isMidStop) {
                variant = "犯规";
                return variant;
            }
            break;
        }
        case UploadStatus:
        {

            int status = QSqlTableModel::data(index).toInt();
//            qDebug() << __func__ << __LINE__ << index.row() << index.column() << QSqlTableModel::data(index);
            if (status == 1) {
                return QVariant("已上传");
            } else if (status == 0) {
                return QVariant("未上传");
            }
            break;
        }
        case OnlineOffline:
        {
            int status = QSqlTableModel::data(index).toInt();
            if (status == 1) {
                return QVariant("在线");
            } else if (status == 0) {
                return QVariant("离线");
            }
        }
        default:
            break;
        }
        return QSqlTableModel::data(index);
    }
    return QVariant();
}

Qt::ItemFlags LocalStudentTableModel::flags(const QModelIndex &index) const
{
    return QSqlTableModel::flags(index);
}


void LocalStudentTableModel::updateModel()
{
    beginResetModel();
    endResetModel();
}

QVariant LocalStudentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        TableColumn column = static_cast<TableColumn>(section);
        switch (column) {
        case Zkh:
            return "准考号";
        case Name:
            return QString("姓名");
        case Gender:
            return QString("性别");
        case Project:
            return QString("项目");
        case FirstScore:
            return QString("第一次成绩  ");
        case SecondScore:
            return QString("第二次成绩 ");
        case ThirdScore:
            return QString("第三次成绩 ");
        case ExamTime:
            return QString("时间");
        case UploadStatus:
            return QString("上传状态 ");
        case OnlineOffline:
            return QString("在线/离线");
        case ErrorMsg:
            return QString("错误消息");        
        case VideoPath:
            return QString("现场视频");
        default:
            break;
        }
    }
    return QVariant();
}
