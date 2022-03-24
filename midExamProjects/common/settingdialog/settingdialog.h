#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
signals:
    void sigReStartApp();
private slots:
    void on_pbSetNetwork_clicked();

    void on_pbSetVideo_clicked();

    void on_pbSetExam_clicked();

    void on_pbSetCheck_clicked();

    void on_pbCloseSetting_clicked();

    void on_pbChangeVideoPath_clicked();

    void on_buttonBox_accepted();

//    void on_rbOnlineMode_toggled(bool checked);

//    void on_rbOfflineMode_toggled(bool checked);

private:
    Ui::SettingDialog *ui;

    void initPushButton();
    void initSettingUIValue();

    const QString m_unchecked = QString::fromUtf8("font: 25 12pt \"Microsoft YaHei\";\n"
                                                  "color: rgb(181, 180, 188);\n"
                                                  "background-color: rgb(36, 34, 49);\n"
                                                  "border:none;");
    const QString m_checked = QString::fromUtf8("font: 25 12pt \"Microsoft YaHei\";\n"
                                                "color: rgb(181, 180, 188);\n"
                                                "background-color: rgb(87, 144, 255);\n"
                                                "border:none;");
};

#endif // SETTINGDIALOG_H
