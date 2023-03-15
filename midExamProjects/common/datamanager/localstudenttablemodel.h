#ifndef LOCALSTUDENTTABLEMODEL_H
#define LOCALSTUDENTTABLEMODEL_H


#include <QtCore/QAbstractTableModel>
#include <QtCore/QHash>
#include <QtCore/QRect>
#include "networkserver.h"
#include "Student.h"
#include <QSqlTableModel>
#include "utils.h"

static QSqlError addScore(const QString &zkh,
                          const QString &name,
                          int gender,
                          const QString &examProject,
                          int firstScore,
                          int secondScore,
                          int thirdScore,
                          bool midStop,
                          const QDateTime &examTime,
                          int uploadStatus,
                          const QString &errorMsg,
                          const QString &onSiteVide);

enum TableColumn {
    Zkh,
    Id,
    Name,
    Gender,
    Project,
    FirstScore,
    SecondScore,
    ThirdScore,
    MidStopFirst,
    MidStopSecond,
    MidStopThird,
    ExamCount,
    ExamTime,
    ExamFirstStartTime,
    ExamFirstStopTime,
    ExamSecondStartTime,
    ExamSecondStopTime,
    ExamThirdStartTime,
    ExamThirdStopTime,
    UploadStatus,
    OnlineOffline,
    ErrorMsg,    
    VideoPath
};

class LocalStudentTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit LocalStudentTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

//    void insertRow(int position, const QModelIndex &parent = QModelIndex());

public slots:
//    void schoolListDataChanged();
private:
    QString dataTextStr = "yyyy-MM-dd hh:mm:ss ddd";
public:
    void updateModel();
};

#endif // LOCALSTUDENTTABLEMODEL_H
