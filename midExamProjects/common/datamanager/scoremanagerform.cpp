#include "scoremanagerform.h"
#include "ui_scoremanagerform.h"
#include "networkserver.h"
#include "singleton.h"
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QMessageBox>

ScoreManagerForm::ScoreManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreManagerForm)
{
    ui->setupUi(this);
    initScoreModel();
}

ScoreManagerForm::~ScoreManagerForm()
{
    delete ui;
}

void ScoreManagerForm::initScoreModel()
{
    // 1. init examed student
    if (m_scoreModel == nullptr) {

        m_scoreModel = new LocalStudentTableModel(this);
        m_scoreModel->setTable("scores");

        m_scoreProxyModel = new MySortFilterProxyModel(this);
        m_scoreProxyModel->setSourceModel(m_scoreModel);


        ui->tblViewStudentData->setModel(m_scoreProxyModel);
        ui->tblViewStudentData->setColumnHidden(Id, true);

        ui->tblViewStudentData->setColumnHidden(MidStopFirst, true);
        ui->tblViewStudentData->setColumnHidden(MidStopSecond, true);
        ui->tblViewStudentData->setColumnHidden(MidStopThird, true);

        ui->tblViewStudentData->setColumnHidden(ExamFirstStartTime, true);
        ui->tblViewStudentData->setColumnHidden(ExamFirstStopTime, true);
        ui->tblViewStudentData->setColumnHidden(ExamSecondStartTime, true);
        ui->tblViewStudentData->setColumnHidden(ExamSecondStopTime, true);
        ui->tblViewStudentData->setColumnHidden(ExamThirdStartTime, true);
        ui->tblViewStudentData->setColumnHidden(ExamThirdStopTime, true);
        ui->tblViewStudentData->setColumnHidden(ExamCount, true);

        ui->tblViewStudentData->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tblViewStudentData->verticalHeader()->setHidden(true);

        connect(this, &ScoreManagerForm::sigLocalStudentsDataChanged, this, &ScoreManagerForm::handleUpdateScoreModel);
        NetWorkServer &server = Singleton<NetWorkServer>::GetInstance();
        connect(&server, &NetWorkServer::sigStudentScoreUploaded, this, &ScoreManagerForm::handleUpdateScoreModel);

        handleUpdateScoreModel();
    }
}

void ScoreManagerForm::handleUpdateScoreModel()
{
    m_scoreModel->updateModel();
    m_scoreModel->select();
}

void ScoreManagerForm::on_pbSearch_clicked()
{
    // search from model by student id, start date, and end date
    // search from model by student id, start date, and end date
    QString zkh = ui->leStudentZkh->text();
    QDateTime dateTimeFrom = ui->dateTimeFrom->dateTime();
    QDateTime dateTimeTo = ui->dateTimeTo->dateTime();
    if (m_scoreProxyModel != nullptr) {
        m_scoreProxyModel->setFilterFixedString(zkh);
        m_scoreProxyModel->setFilterMinimumDate(dateTimeFrom);
        m_scoreProxyModel->setFilterMaximumDate(dateTimeTo);
    }
}


void ScoreManagerForm::on_tblViewStudentData_doubleClicked(const QModelIndex &index)
{
    qDebug() << __func__ << __LINE__ << index.row() << index.column() << index.data();
    if (index.column() == VideoPath) {
        QString file = index.data().toString();
        QFileInfo fileInfo(file);
        QDir dir(fileInfo.absolutePath());
        if (!dir.exists()) {
            QMessageBox::warning(this, "警告", "文件夹不存在");
            return;
        }
        QDesktopServices::openUrl(fileInfo.absolutePath());
    }
}
