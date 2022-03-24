#ifndef LOCALSTUDENTTABLEMODEL_H
#define LOCALSTUDENTTABLEMODEL_H


#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include "networkserver.h"
#include "TmpStudent.h"

enum TableColumn {
    Zkh,
    Name,
    Gender,
    Project,
    FirstScore,
    SecondScore,
    ThirdScore,
    Time,
    UploadStatus,
    ErrorMsg,
    OnlineOffline,
    VideoPath
};

class LocalStudentTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit LocalStudentTableModel(QList<TmpStudent*> &schools, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void insertRow(int position, const QModelIndex &parent = QModelIndex());
    void addMapping(QString color, QRect area);
    void clearMapping() { m_mapping.clear(); }
public slots:
    void schoolListDataChanged();
private:
    QList<TmpStudent*> &m_students;
    QList<QVector<qreal> * > m_data;
    QHash<QString, QRect> m_mapping;
    int m_columnCount;
    int m_rowCount;

    // QAbstractItemModel interface
public:
    void updateModel();
};

#endif // LOCALSTUDENTTABLEMODEL_H
