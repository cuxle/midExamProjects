#pragma execution_character_set("utf-8")
#include "scoremanagerform.h"
#include "ui_scoremanagerform.h"
#include "networkserver.h"
#include "appconfig.h"
#include "singleton.h"
#include <QFileInfo>
#include <QDir>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileDialog>

ScoreManagerForm::ScoreManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreManagerForm)
{
    ui->setupUi(this);

    initScoreModel();

    connect(ui->pbExportXlsx, &QPushButton::clicked, this, &ScoreManagerForm::handleExportXlsxData);
}

ScoreManagerForm::~ScoreManagerForm()
{
    delete ui;
}

void ScoreManagerForm::saveStudentScore(const QString &xlsxFileName)
{
    /*
     * enum StuColumn{
    StuStart = 1,
    StuID = StuStart,
    StuName,
    StuNum,
    StuGender,
    StuSchool,
    StuExamItem,
    StuScore,
    Stu1stScore,
    Stu2stScore,
    Stu3stScore,
    StuExamTime,
    StuUploadStatus,
    StuErrorInfo,
    StuVideoPath,
    StuEnd = StuVideoPath
     *
     */
    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
    QString m_videoPath = appconfig.m_videoSavePath;

    if (m_xlsx != nullptr) {
        delete m_xlsx;
        m_xlsx = nullptr;
    }
    m_xlsx = new QXlsx::Document(xlsxFileName);
    qDebug() << __func__ << __LINE__ << xlsxFileName;
    writeHeader(*m_xlsx);

    for (int i = 0; i < m_scoreModel->rowCount(); i++) {
        int m_rowsInXlsx = i + 2;
        m_xlsx->write(m_rowsInXlsx, Zkh+1, m_scoreModel->data(m_scoreModel->index(i, Zkh)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+2, m_scoreModel->data(m_scoreModel->index(i, Name)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+3, m_scoreModel->data(m_scoreModel->index(i, Gender)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+4, m_scoreModel->data(m_scoreModel->index(i, Project)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+5, m_scoreModel->data(m_scoreModel->index(i, FirstScore)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+6, m_scoreModel->data(m_scoreModel->index(i, SecondScore)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+7, m_scoreModel->data(m_scoreModel->index(i, ThirdScore)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+8, m_scoreModel->data(m_scoreModel->index(i, ExamTime)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+9, m_scoreModel->data(m_scoreModel->index(i, UploadStatus)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+10, m_scoreModel->data(m_scoreModel->index(i, OnlineOffline)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+11, m_scoreModel->data(m_scoreModel->index(i, ErrorMsg)).toString());
        m_xlsx->write(m_rowsInXlsx, Zkh+12, m_scoreModel->data(m_scoreModel->index(i, VideoPath)).toString());
        qDebug() << __func__ << __LINE__ << i << xlsxFileName;
    }

    m_xlsx->save();
}

void ScoreManagerForm::writeHeader(QXlsx::Document &xlsx)
{
    const QStringList m_xlsxHeader{"", "zkh", "name", "gender", "project", "firstScore",  "secondScore", "thirdScore", "examTime",
                                      "uploadStatus", "online", "errorMsg", "videoPath"};
    int headRow = 1;
    for (int i = 1; i < m_xlsxHeader.size(); i++) {
        qDebug() << __func__ << __LINE__ << i;

        m_xlsx->write(headRow, i, m_xlsxHeader.at(i));
    }
    m_xlsx->save();
}
void ScoreManagerForm::initXlsxDcoment()

{
//    AppConfig &appconfig = Singleton<AppConfig>::GetInstance();
//    QString m_videoPath = appconfig.m_videoSavePath;
//    QString xlsxFileName = m_videoPath + "/" + "data.xlsx";
//    QFile file(xlsxFileName);
//    m_xlsx = new QXlsx::Document(xlsxFileName);
//    if (!file.exists()) {
//        // set file header
//        /* const QStringList m_xlsxHeader = {"", QStringLiteral("序号 "), QStringLiteral("姓名 "),  QStringLiteral("学号 "), QStringLiteral("性别 "), QStringLiteral("学校 "), QStringLiteral("考试项目 "),
//                                          QStringLiteral("考试成绩 "), QStringLiteral("第一次考试成绩 "), QStringLiteral("第二次考试成绩 "), QStringLiteral("第三次考试成绩 "),
//                                          QStringLiteral("考试时间 "), QStringLiteral("上传状态 "), QStringLiteral("错误信息 "), QStringLiteral("视频路径 ")};
//        */
//        const QStringList m_xlsxHeader = {"", "Index", "Name", "ID", "Gender", "School", "ExamProject", "Finial Score", "First Score", "Second Score", "Third Score", "Exam Time", "Upload Status", "Error Message", "Video Path"};
//        int headRow = 1;
//        for (int i = StuIndex; i <= StuVideoPath; i++) {
//            m_xlsx->write(headRow, i, m_xlsxHeader.at(i));
//        }
//        m_xlsx->save();
//        m_rowsInXlsx++;

//    } else {

//        while (m_rowsInXlsx) {
//            QVariant data = m_xlsx->read(m_rowsInXlsx, 1);
//            if (data.isNull()) {
//                break;
//            }
//            m_rowsInXlsx++;
//        }
//    }
//    qDebug() << __func__ << __LINE__ << m_rowsInXlsx;
}

void ScoreManagerForm::handleExportXlsxData()
{
    AppConfig &appConfig = Singleton<AppConfig>::GetInstance();

    QString fileName = QFileDialog::getSaveFileName(this, "Export Xlsx File", appConfig.m_videoSavePath, tr("Xlsx Files (*.xlsx)"));
    if (fileName.isEmpty()) return;

    saveStudentScore(fileName);
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

//        connect(this, &ScoreManagerForm::sigLocalStudentsDataChanged, this, &ScoreManagerForm::handleUpdateScoreModel);
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
