#include "scoremanagerform.h"
#include "ui_scoremanagerform.h"
#include "networkserver.h"
#include "singleton.h"

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

