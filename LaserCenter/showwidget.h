#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTableView>
#include <QPushButton>
#include "qcustomplot.h"

class ShowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShowWidget(QWidget *parent = nullptr);

public:
    QTableWidget    *table1;
    QTableWidget    *table2;

    QTableView      *resultView;
    QTableView      *resultView2;

    QPushButton     *saveBtn;

    QCustomPlot     *cp1;
    QCustomPlot     *cp2;
    QCPGraph        *graph1;
    QCPGraph        *graph2;

private:
    QStandardItemModel model;
    QStandardItemModel model2;
    QList<QStandardItem *> items;

    QLabel          *label1;
    QLabel          *label2;
    QLabel          *label3;
    QLabel          *label4;
    QLabel          *label5;
    QLabel          *label6;
    QLabel          *label7;
    QLabel          *label8;
    QLabel          *label9;
    QLabel          *label10;
signals:

};

#endif // SHOWWIDGET_H
