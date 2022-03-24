#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    FormLogin *login = qobject_cast<FormLogin*>(ui->widget);
    connect(login, &FormLogin::sigExitApp, this, &LoginDialog::exitApp);
    connect(login, &FormLogin::sigHiddenLoginForm, this, &LoginDialog::hiddenLoginForm);
}

LoginDialog::~LoginDialog()
{
    qDebug() << __FUNCTION__;
    delete ui;
}

void LoginDialog::exitApp()
{
    this->close();
}

void LoginDialog::hiddenLoginForm()
{
    this->setHidden(true);
}
