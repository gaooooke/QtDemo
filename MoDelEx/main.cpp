#include "mainwindow.h"

#include <QApplication>
#include <QTableView>
#include "modelex.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModelEx modelEx;
    QTableView view;
    view.setModel(&modelEx);
    view.setWindowTitle(QObject::tr("ModelEx"));
    view.resize(400,400);
    view.show();

//    MainWindow w;
//    w.show();
    return a.exec();
}
