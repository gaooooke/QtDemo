#include "showwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSplitter>
#include <QStandardItemModel>
#include <QFrame>

ShowWidget::ShowWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout     *leftLayout     =       new QVBoxLayout();

    resultView =  new QTableView();
    resultView->setFixedSize(300,200);
    resultView2 = new QTableView();
    resultView2->setFixedWidth(300);
//! [set up the model]

    model.setHorizontalHeaderLabels({ QApplication::translate("nestedlayouts", "设备号"),
                                      QApplication::translate("nestedlayouts", "左右相机"),
                                      QApplication::translate("nestedlayouts", "相机MAC"),
                                      QApplication::translate("nestedlayouts", "设备状态") });

    const QStringList rows[] = {
        QStringList{ QStringLiteral("0-0"), QStringLiteral("左相机"),QStringLiteral("00:111c:f5:ba:b6"), QStringLiteral("未连接") },
        QStringList{ QStringLiteral("0-1"), QStringLiteral("右相机"),QStringLiteral("00:111c:f5:ba:b6"), QStringLiteral("未连接") }
    };


    for (const QStringList &row : rows) {
        items.clear();
        for (const QString &text : row)
            items.append(new QStandardItem(text));
        model.appendRow(items);
    }

    resultView->setModel(&model);
    resultView->verticalHeader()->hide();
    resultView->horizontalHeader()->setStretchLastSection(false);

    model2.setHorizontalHeaderLabels({ QApplication::translate("nestedlayouts", "参数"),
                                      QApplication::translate("nestedlayouts", "当前值"),
                                      QApplication::translate("nestedlayouts", "说明")});

    const QStringList rows2[] = {
        QStringList{ QStringLiteral("0-0"), QStringLiteral("左相机"),QStringLiteral("00:111c:f5:ba:b6") },
        QStringList{ QStringLiteral("0-1"), QStringLiteral("右相机"),QStringLiteral("00:111c:f5:ba:b6") },
        QStringList{ QStringLiteral("0-1"), QStringLiteral("右相机"),QStringLiteral("00:111c:f5:ba:b6") }
    };


    for (const QStringList &row : rows2) {
        items.clear();
        for (const QString &text : row)
            items.append(new QStandardItem(text));
        model2.appendRow(items);
    }


    resultView2->setModel(&model2);
    resultView2->verticalHeader()->hide();
    resultView2->horizontalHeader()->setStretchLastSection(false);

////    QTableView *resultView2 = new QTableView();
////! [set up the model]

    saveBtn =   new QPushButton("保存");
    leftLayout->addWidget(resultView);
    leftLayout->addWidget(resultView2);
    leftLayout->addStretch();
    leftLayout->addWidget(saveBtn);
    leftLayout->addStretch();
//   leftLayout->setSizeConstraint(QLayout::SetFixedSize);


    QHBoxLayout     *rightLayout    =       new QHBoxLayout();
    cp1            =        new QCustomPlot;

 //   cp1->axisRect()->setupFullAxesBox();
    cp1->xAxis->setRange(-100,100);
    cp1->yAxis->setRange(-20,200);
    cp1->xAxis2->setVisible(true);
    cp1->yAxis2->setVisible(true);

    cp1->xAxis->ticker()->setTickCount(10);
    cp1->xAxis2->ticker()->setTickCount(10);
    cp1->yAxis->ticker()->setTickCount(10);
    cp1->yAxis2->ticker()->setTickCount(10);
//    cp1->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);

    QPen pen;
    pen.setWidth(2);
    cp1->xAxis->setTickPen(pen);
    cp1->xAxis->setTickLengthOut(5);
    cp1->yAxis->setTickPen(pen);
    cp1->yAxis->setTickLengthOut(5);
    cp1->xAxis2->setTickPen(pen);
    cp1->xAxis2->setTickLengthOut(5);
    cp1->yAxis2->setTickPen(pen);
    cp1->yAxis2->setTickLengthOut(5);

    cp1->xAxis2->setRange(-100,100);
    cp1->yAxis2->setRange(-20,200);
    cp1->xAxis->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
    cp1->yAxis->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
    cp1->xAxis2->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
    cp1->yAxis2->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
    cp1->xAxis->grid()->setPen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
    cp1->yAxis->grid()->setPen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
    cp1->xAxis->grid()->setZeroLinePen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
    cp1->yAxis->grid()->setZeroLinePen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
    cp1->xAxis->grid()->setSubGridVisible(true);
    cp1->yAxis->grid()->setSubGridVisible(true);

    graph1 =    cp1->addGraph();
    cp1->graph(0)->setPen(QPen(Qt::blue));
    cp1->xAxis->setTicks(true);

    cp1->setInteractions(QCP::iRangeZoom);




   cp2            =        new QCustomPlot;

   cp2->xAxis->setTickPen(pen);
   cp2->xAxis->setTickLengthOut(5);
   cp2->yAxis->setTickPen(pen);
   cp2->yAxis->setTickLengthOut(5);
   cp2->xAxis2->setTickPen(pen);
   cp2->xAxis2->setTickLengthOut(5);
   cp2->yAxis2->setTickPen(pen);
   cp2->yAxis2->setTickLengthOut(5);

   cp2->xAxis->setLabelFont(QFont("Time New Roman",12));


   cp2->xAxis->setRange(-100,100);
   cp2->yAxis->setRange(-20,200);
   cp2->xAxis2->setVisible(true);
   cp2->yAxis2->setVisible(true);

   cp2->xAxis->ticker()->setTickCount(10);
   cp2->xAxis2->ticker()->setTickCount(10);
   cp2->yAxis->ticker()->setTickCount(10);
   cp2->yAxis2->ticker()->setTickCount(10);
//    cp1->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);

   cp2->xAxis2->setRange(-100,100);
   cp2->yAxis2->setRange(-20,120);
   cp2->xAxis->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
   cp2->yAxis->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
   cp2->xAxis2->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
   cp2->yAxis2->setBasePen(QPen(QColor(Qt::black),3,Qt::PenStyle::SolidLine));
   cp2->xAxis->grid()->setPen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
   cp2->yAxis->grid()->setPen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
   cp2->xAxis->grid()->setZeroLinePen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
   cp2->yAxis->grid()->setZeroLinePen(QPen(QColor(158,158,158),2,Qt::PenStyle::DashLine));
   cp2->xAxis->grid()->setSubGridVisible(true);
   cp2->yAxis->grid()->setSubGridVisible(true);

   graph2   =   cp2->addGraph(0);
   cp2->graph(0)->setPen(QPen(Qt::blue));
   cp2->xAxis->setTicks(true);

   cp2->setInteractions(/*QCP::iRangeDrag | */ QCP::iRangeZoom);




//    rightLayout->addLayout(leftLayout);
    rightLayout->addWidget(cp1);
    rightLayout->addWidget(cp2);

    QHBoxLayout     *topLayout      =       new QHBoxLayout();
    topLayout->addLayout(leftLayout);
    topLayout->addLayout(rightLayout);


    QGridLayout     *bottomLayout   =       new QGridLayout();
    label1         =       new QLabel("左>  数据点数：");
    label2         =       new QLabel("匹配时间：");
    label3         =       new QLabel("匹配最大偏差：");
    label4         =       new QLabel("匹配平均偏差：");
    label5         =       new QLabel("匹配置信度：");
    label6         =       new QLabel("右>  数据点数：");
    label7         =       new QLabel("匹配时间：");
    label8         =       new QLabel("匹配最大偏差：");
    label9         =       new QLabel("匹配平均偏差：");
    label10         =       new QLabel("匹配置信度：");

    bottomLayout->addWidget(label1,0,0);
    bottomLayout->addWidget(label2,0,1);
    bottomLayout->addWidget(label3,0,2);
    bottomLayout->addWidget(label4,0,3);
    bottomLayout->addWidget(label5,0,4);
    bottomLayout->addWidget(label6,1,0);
    bottomLayout->addWidget(label7,1,1);
    bottomLayout->addWidget(label8,1,2);
    bottomLayout->addWidget(label9,1,3);
    bottomLayout->addWidget(label10,1,4);
 //   bottomLayout->setAlignment(Qt::AlignCenter);

    bottomLayout->setSizeConstraint(QLayout::SetFixedSize);

    QVBoxLayout     *mainLayout     =       new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

 //   mainLayout->setStretchFactor(mainLayout,1);

 //   mainLayout->setSizeConstraint(QLayout::SetFixedSize);

}
