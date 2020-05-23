#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QToolButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("激光对中软件");

    showWidget      =       new ShowWidget(this);
    setCentralWidget(showWidget);

    createActions();
    createToolBars();

//    railtype    =   75;
//    loadRailModelPoint(75);
    drawStdRail(75);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    //检测控制
    startAction    =       new QToolButton;
    startAction->setText("启动检测");
    startAction->setIcon(QPixmap(":/res/start.bmp"));
    startAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    startAction->setShortcut(tr("Ctrl+S"));

    stopAction    =       new QToolButton;
    stopAction->setText("停止检测");
    stopAction->setIcon(QPixmap(":/res/stop.bmp"));
    stopAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    stopAction->setShortcut(tr("Ctrl+E"));


    //轨型切换
    rail50Action    =       new QToolButton;
    rail50Action->setText("50轨");
    rail50Action->setIcon(QPixmap(":/res/50.bmp"));
    rail50Action->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    rail50Action->setStyleSheet("QToolButton{border:none;background:transparent;}");
    connect(rail50Action,&QToolButton::clicked,[=](){
//        railtype=50;
        drawStdRail(50);
    });

    rail60Action    =       new QToolButton;
    rail60Action->setText("60轨");
    rail60Action->setIcon(QPixmap(":/res/60.bmp"));
    rail60Action->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(rail60Action,&QToolButton::clicked,[=](){
//        railtype=60;
        drawStdRail(60);
    });


    rail75Action    =       new QToolButton;
    rail75Action->setText("75轨");
    rail75Action->setIcon(QPixmap(":/res/75.bmp"));
    rail75Action->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(rail75Action,&QToolButton::clicked,[=](){
//        railtype=75;
        drawStdRail(75);
    });

    autoRailAction    =       new QToolButton;
    autoRailAction->setText("自动切换");
    autoRailAction->setIcon(QPixmap(":/res/auto.bmp"));
    autoRailAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    autoRailAction->setStyleSheet("background-color:rgba(0,0,0,0)");

    //参数配置
    importParamAction    =       new QToolButton;
    importParamAction->setText("导入默认参数");
    importParamAction->setIcon(QPixmap(":/res/file.bmp"));
    importParamAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    showParamAction    =       new QToolButton;
    showParamAction->setText("显示参数设置");
    showParamAction->setIcon(QPixmap(":/res/set.bmp"));
    showParamAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(showParamAction,&QToolButton::clicked,[=](){
        showSetting();
    });

    //相机设置
    leftCamAction    =       new QToolButton;
    leftCamAction->setText("左相机设置");
    leftCamAction->setIcon(QPixmap(":/res/cam.bmp"));
    leftCamAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    rightCamAction    =       new QToolButton;
    rightCamAction->setText("右相机设置");
    rightCamAction->setIcon(QPixmap(":/res/cam.bmp"));
    rightCamAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //数据管理
    saveXYAction    =       new QToolButton;
    saveXYAction->setText("Save XY");
    saveXYAction->setIcon(QPixmap(":/res/openfile.jpg"));
    saveXYAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    saveErrAction    =       new QToolButton;
    saveErrAction->setText("Save Err");
    saveErrAction->setIcon(QPixmap(":/res/txt.bmp"));
    saveErrAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    showStatisticsAction    =       new QToolButton;
    showStatisticsAction->setText("数据统计");
    showStatisticsAction->setIcon(QPixmap(":/res/tj.bmp"));
    showStatisticsAction->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    showWidget->resultView->hide();
    showWidget->resultView2->hide();
    showWidget->saveBtn->hide();

}

void MainWindow::createToolBars()
{
    //检测控制
    startOperator       =       addToolBar("检测控制");
    startOperator->addWidget(startAction);
    startOperator->addWidget(stopAction);
    startOperator->setAllowedAreas(Qt::TopToolBarArea);
    startOperator->setMovable(false);

    //轨型切换
    railSelection       =       addToolBar("轨型切换");
    railSelection->addWidget(rail50Action);
    railSelection->addWidget(rail60Action);
    railSelection->addWidget(rail75Action);
    railSelection->addSeparator();
    railSelection->addWidget(autoRailAction);
    railSelection->setAllowedAreas(Qt::TopToolBarArea);
    railSelection->setMovable(false);

    //参数配置
    paramSetting        =       addToolBar("参数配置");
    paramSetting->addWidget(importParamAction);
    paramSetting->addWidget(showParamAction);
    paramSetting->setAllowedAreas(Qt::TopToolBarArea);
    paramSetting->setMovable(false);

    //相机设置
    camSetting          =       addToolBar("相机设置");
    camSetting->addWidget(leftCamAction);
    camSetting->addWidget(rightCamAction);
    camSetting->setAllowedAreas(Qt::TopToolBarArea);
    camSetting->setMovable(false);

    //数据管理
    dataOperator        =       addToolBar("数据管理");
    dataOperator->addWidget(saveXYAction);
    dataOperator->addWidget(saveErrAction);
    dataOperator->addWidget(showStatisticsAction);
    dataOperator->setAllowedAreas(Qt::TopToolBarArea);
    dataOperator->setMovable(false);
}

void MainWindow::showSetting()
{
    QString name = showParamAction->text();

    if("显示参数设置"==name)
    {
        showParamAction->setText("隐藏参数设置");
        showWidget->resultView->show();
        showWidget->resultView2->show();
        showWidget->saveBtn->show();
    }
    if("隐藏参数设置"==name)
    {
        showParamAction->setText("显示参数设置");
        showWidget->resultView->hide();
        showWidget->resultView2->hide();
        showWidget->saveBtn->hide();
    }
}

bool MainWindow::readTxt(QString txtPath)
{
    QFile  file(txtPath);
    xVec.clear();
    yVec.clear();

    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream textStream(&file);
        while(!textStream.atEnd())
        {
            QString lineTxt =  textStream.readLine();

            if (lineTxt == "" || lineTxt ==" ")
               continue;

            bool ok;
            if(lineTxt.endsWith(";"))
            {
                QStringList strlist = lineTxt.split(";");

                if(strlist.at(0).trimmed().split("=").at(0).trimmed()=="nRailType")
                {
                    nRailType = strlist.at(0).trimmed().split("=").at(1).trimmed().toInt(&ok);
                }
                if(strlist.at(0).trimmed().split("=").at(0).trimmed()=="nCornerIndex")
                {
                    nCornerIndex = strlist.at(0).trimmed().split("=").at(1).trimmed().toInt(&ok);
                }
                if(strlist.at(0).trimmed().split("=").at(0).trimmed()=="dbWebEndY")
                {
                    dbWebEndY = strlist.at(0).trimmed().split("=").at(1).trimmed().toDouble(&ok);
                }
                if(strlist.at(0).trimmed().split("=").at(0).trimmed()=="dbWearRegionUpLimit")
                {
                    dbWearRegionUpLimit = strlist.at(0).trimmed().split("=").at(1).trimmed().toDouble(&ok);
                }
            }
            else
            {
                QStringList pointlist   =   lineTxt.split(QRegExp("[\t \t\t \t\t\t ]"));
                double x = pointlist.at(0).trimmed().toDouble(&ok);
                double y = pointlist.at(1).trimmed().toDouble(&ok);
                xVec.push_back(x);
                xVec.push_back(-x);
                yVec.push_back(y);
                yVec.push_back(y);
            }
        }
    }
    return true;
}

void MainWindow::loadRailModelPoint(int railtype)
{
    if(railtype==50 || railtype == 60 || railtype ==75 )
    {
        //此处修改为相对路径
        if(50 == railtype)
        {
            QString rail50  =   "C:/Users/little chen/Desktop/Qt/LaserCenter/RailModel/model50.txt";
            readTxt(rail50);
        }
        if(60 == railtype)
        {
            QString rail60  =   "C:/Users/little chen/Desktop/Qt/LaserCenter/RailModel/model60.txt";
            readTxt(rail60);
        }
        if(75 == railtype)
        {
            QString rail75  =   "C:/Users/little chen/Desktop/Qt/LaserCenter/RailModel/model75.txt";
            readTxt(rail75);
        }
    }
}

void MainWindow::showStdRailPoint(QCPGraph *cpg)
{
    QPen    drawPen;
    drawPen.setColor(Qt::blue);
    drawPen.setWidth(2);

    cpg->setPen(drawPen);
    cpg->setLineStyle(QCPGraph::lsNone);
    cpg->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,2));

//    cpg->setData(xVecN,yVec);
    cpg->setData(xVec,yVec);

}

void MainWindow::drawStdRail(int railtype)
{
//    railtype=nRailType;
    showWidget->cp1->replot();
    showWidget->cp2->replot();
    loadRailModelPoint(railtype);

    showStdRailPoint(showWidget->graph1);
    showStdRailPoint(showWidget->graph2);
}

//void MainWindow::showCam()
//{

//}
