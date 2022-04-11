#ifndef SCOREMANAGERFORM_H
#define SCOREMANAGERFORM_H

#include <QWidget>
#include "mysortfilterproxymodel.h"

#include "localstudenttablemodel.h"
#include "xlsxdocument.h"

namespace Ui {
class ScoreManagerForm;
}

class ScoreManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreManagerForm(QWidget *parent = nullptr);
    ~ScoreManagerForm();
public slots:
    void handleUpdateScoreModel();
private slots:
    void on_pbSearch_clicked();
    void on_tblViewStudentData_doubleClicked(const QModelIndex &index);
    void handleExportXlsxData();
signals:
    void sigLocalStudentsDataChanged();
private:
    Ui::ScoreManagerForm *ui;
    void initScoreModel();
    void initXlsxDcoment();
    void saveStudentScore(const QString &fileName);
    void writeHeader(QXlsx::Document &xlsx);

    LocalStudentTableModel *m_scoreModel = nullptr;
    MySortFilterProxyModel *m_scoreProxyModel = nullptr;

    QXlsx::Document * m_xlsx = nullptr;
};

#endif // SCOREMANAGERFORM_H
