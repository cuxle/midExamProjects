#ifndef SCOREMANAGERFORM_H
#define SCOREMANAGERFORM_H

#include <QWidget>
#include "mysortfilterproxymodel.h"

#include "localstudenttablemodel.h"

namespace Ui {
class ScoreManagerForm;
}

class ScoreManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreManagerForm(QWidget *parent = nullptr);
    ~ScoreManagerForm();
private slots:
    void handleUpdateScoreModel();
    void on_pbSearch_clicked();
    void on_tblViewStudentData_doubleClicked(const QModelIndex &index);
signals:
    void sigLocalStudentsDataChanged();
private:
    Ui::ScoreManagerForm *ui;
    void initScoreModel();

    LocalStudentTableModel *m_scoreModel = nullptr;
    MySortFilterProxyModel *m_scoreProxyModel = nullptr;
};

#endif // SCOREMANAGERFORM_H
