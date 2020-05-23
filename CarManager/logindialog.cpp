#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include "connection.h"
//
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    setFixedSize(300,200);
    setWindowTitle("登录");
    ui->pwdLineEdit->setFocus();
    ui->loginBtn->setDefault(true);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    if(ui->pwdLineEdit->text().isEmpty())
    {
        QMessageBox::information(this,"请输入密码","请先输入密码再登陆",QMessageBox::Ok);
        ui->pwdLineEdit->setFocus();
    }
    else
    {
        QSqlQuery query;
        query.exec("select pwd from password");
        query.next();
        if(query.value(0).toString() == ui->pwdLineEdit->text())
        {
            QDialog::accept();
        }
        else
        {
            QMessageBox::warning(this,"面膜错误","请输入争取的密码再登陆",QMessageBox::Ok);
            ui->pwdLineEdit->clear();
            ui->pwdLineEdit->setFocus();
        }
    }
}

void LoginDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}
