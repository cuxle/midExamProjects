﻿#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>
#include "networkServer/networkserver.h"

namespace Ui {
class FormLogin;
}

class FormFuncChoose;

class FormLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FormLogin(QWidget *parent = 0);
    ~FormLogin();
signals:
    void sigExitApp();
    void sigHiddenLoginForm();

private slots:
    void on_pbLoginOffline_clicked();

    void on_pbExit_clicked();

    void on_pbLoginOnline_clicked();

    void hanldeLoginStateChanged(bool isLogin);
private:

    void initMainFrm(bool online);

    void updateUserNameListInfo(const QString &arg1);
    Ui::FormLogin *ui;

    FormFuncChoose *m_frmFuncChoose = nullptr;

//    NetWorkServer *m_server = nullptr;
};

#endif // FORMLOGIN_H
