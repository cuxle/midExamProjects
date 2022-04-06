#pragma execution_character_set("utf-8")

#include "localstudenttablemodel.h"
#include <QStringLiteral>
#include <QFont>
#include <QColor>

LocalStudentTableModel::LocalStudentTableModel(QList<Student*> &students, QObject *parent) :
    QAbstractTableModel(parent),
    m_students(students)
{
    m_columnCount = 12;
    qDebug() << __func__ << m_students.size();
}

int LocalStudentTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_students.count();
}

int LocalStudentTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_columnCount;
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
        if ((index.column() == FirstScore && m_students[index.row()]->midStopFirst) ||
                (index.column() == SecondScore && m_students[index.row()]->midStopSecond) ||
                (index.column() == ThirdScore && m_students[index.row()]->midStopThird)) {
            color = Qt::red;
        }
        return QVariant::fromValue(color);
    } else if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case Zkh:
            return m_students[index.row()]->zkh;
        case Name:
            return m_students[index.row()]->name;
        case Gender:
            return m_students[index.row()]->gender == 1 ? "男" : "女";
        case Project:
            return m_students[index.row()]->examProjectName;
        case FirstScore:
        {
#if defined(FOOTBALL) || defined (BASKETBALL)
            float score = m_students[index.row()]->firstScore;
            score = score / 1000;
            return m_students[index.row()]->midStopFirst ? QVariant("犯规") : QVariant(score);
#else
            return m_students[index.row()]->midStopFirst ? QVariant("中停") : QVariant(m_students[index.row()]->firstScore);
#endif
        }

        case SecondScore:
        {

#if defined(FOOTBALL) || defined (BASKETBALL)
            float score = m_students[index.row()]->secondScore;
            score = score / 1000;
            return m_students[index.row()]->midStopFirst ? QVariant("犯规") : QVariant(score);
#else
            return m_students[index.row()]->midStopFirst ? QVariant("中停") : QVariant(m_students[index.row()]->secondScore);
#endif
        }

        case ThirdScore:
        {
#if defined(FOOTBALL) || defined (BASKETBALL)
            float score = m_students[index.row()]->thirdScore;
            score = score / 1000;
            return m_students[index.row()]->midStopFirst ? QVariant("犯规") : QVariant(score);
#else
            return m_students[index.row()]->midStopFirst ? QVariant("中停") : QVariant(m_students[index.row()]->thirdScore);
#endif
        }

        case Time:
            return m_students[index.row()]->examStartFirstTime;
        case UploadStatus:
            return m_students[index.row()]->uploadStatus == 0 ? "未上传" : "已上传";
        case ErrorMsg:
            return m_students[index.row()]->errorMsg;
        case OnlineOffline:
            return m_students[index.row()]->isOnline ? "在线" : "离线";
        case VideoPath:
            return m_students[index.row()]->videoPath;
        default:
            break;
        }
//        return m_data[index.row()]->at(index.column());
    }
    return QVariant();
}

Qt::ItemFlags LocalStudentTableModel::flags(const QModelIndex &index) const
{
    return QAbstractItemModel::flags(index);
}

void LocalStudentTableModel::insertRow(int position, const QModelIndex &parent)
{
    if ((position < 0) || (position >= m_students.size()))
        return;

    beginInsertRows(parent, position, position);
//	XFrameData fd = m_pSendDatas->at(position);
//    fd.clearFrMsgIndex();
//	m_pSendDatas->insert(position, fd);
//    FRCommander::updateFrMsg2Device(fd, m_pro, true);

    endInsertRows();
}

void LocalStudentTableModel::addMapping(QString color, QRect area)
{
    m_mapping.insertMulti(color, area);
}

void LocalStudentTableModel::schoolListDataChanged()
{
    insertRow(m_students.size() - 1);
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
        case Time:
            return QString("时间");
        case UploadStatus:
            return QString("上传状态 ");
        case ErrorMsg:
            return QString("错误消息");
        case OnlineOffline:
            return QString("在线/离线");
        case VideoPath:
            return QString("现场视频");
        default:
            break;
        }
    }
    return QVariant();
}
