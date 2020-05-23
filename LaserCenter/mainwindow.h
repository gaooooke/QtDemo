#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QSplitter>
#include <QTableWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolButton>
#include "showwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createToolBars();
    void createActions();

    void showStdRailPoint(QCPGraph *cpg);

private:
    Ui::MainWindow *ui;

    QToolButton     *startAction;
    QToolButton     *stopAction;

    QToolButton     *rail50Action;
    QToolButton     *rail60Action;
    QToolButton     *rail75Action;
    QToolButton     *autoRailAction;

    QToolButton     *importParamAction;
    QToolButton     *showParamAction;

    QToolButton     *leftCamAction;
    QToolButton     *rightCamAction;

    QToolButton     *saveXYAction;
    QToolButton     *saveErrAction;
    QToolButton     *showStatisticsAction;

    QToolBar        *startOperator;
    QToolBar        *railSelection;
    QToolBar        *paramSetting;
    QToolBar        *camSetting;
    QToolBar        *dataOperator;

    QSplitter       *splitterMain;
    QSplitter       *splitterLeft;
    QSplitter       *splitterRight;

    ShowWidget      *showWidget;

private:
    int             railtype;
    QVector<double> xVec;
    QVector<double> xVecN;
    QVector<double> yVec;
    void            loadRailModelPoint(int railtype);
    bool            readTxt(QString txtPath);

    int             nRailType;
    int             nCornerIndex;
    double          dbWebEndY;
    double          dbWearRegionUpLimit;

public slots:
    void showSetting();
    void drawStdRail(int railtype);
//    void showCam();


};
#endif // MAINWINDOW_H
