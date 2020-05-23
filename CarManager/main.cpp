#include "mainwindow.h"

#include <QApplication>
#include "connection.h"
#include "logindialog.h"
#include <QDialog>
//
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection() || !createXml())
        return 0;

    MainWindow w;
    LoginDialog login;

    if(login.exec() == QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
    {
        return 0;
    }

}
