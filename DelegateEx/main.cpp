#include "mainwindow.h"

#include <QApplication>
#include <QStandardItemModel>
#include <QTableView>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "datedelegate.h"
#include "combodelegate.h"
#include "spinboxdelegate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStandardItemModel model(4,4);
    QTableView tableView;
    tableView.setModel(&model);

    DateDelegate dateDelegate;
    ComboDelegate comboDelegate;
    SpinBoxDelegate spinBoxDelegate;
    tableView.setItemDelegateForColumn(1,&dateDelegate);
    tableView.setItemDelegateForColumn(2,&comboDelegate);
    tableView.setItemDelegateForColumn(3,&spinBoxDelegate);

    model.setHeaderData(0,Qt::Horizontal,QObject::tr("Name"));
    model.setHeaderData(1,Qt::Horizontal,QObject::tr("Birthday"));
    model.setHeaderData(2,Qt::Horizontal,QObject::tr("Job"));
    model.setHeaderData(3,Qt::Horizontal,QObject::tr("Income"));

//    QString name = QFileDialog::getOpenFileName(NULL,"打开",".","text(*.txt)");
    QString runPath = QCoreApplication::applicationDirPath();
    runPath += "/test.txt";
    QFile file(runPath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString line;

        model.removeRows(0,model.rowCount(QModelIndex()),QModelIndex());

        int row = 0;
        do{
            line = stream.readLine();
            if(!line.isEmpty())
            {
                model.insertRows(row,1,QModelIndex());
                QStringList pieces = line.split(",",QString::SkipEmptyParts);
                model.setData(model.index(row,0,QModelIndex()),pieces.value(0));
                model.setData(model.index(row,1,QModelIndex()),pieces.value(1));
                model.setData(model.index(row,2,QModelIndex()),pieces.value(2));
                model.setData(model.index(row,3,QModelIndex()),pieces.value(3));

                row++;
            }
        }while(!line.isEmpty());
        file.close();
    }
    tableView.setWindowTitle(QObject::tr("Delegate"));
    tableView.resize(520,220);
    tableView.show();

//    MainWindow w;
//    w.show();
    return a.exec();
}
