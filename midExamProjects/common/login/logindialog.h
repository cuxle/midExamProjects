#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "formlogin.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

public slots:
    void exitApp();
    void hiddenLoginForm();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
