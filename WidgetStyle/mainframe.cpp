#include "mainframe.h"
#include "ui_mainframe.h"
#include <QDesktopWidget>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QTextStream>

MainFrame::MainFrame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    initLeftListWidget();
    stylePageInit();



}

MainFrame::~MainFrame()
{
    delete ui;
}

void MainFrame::initLeftListWidget()
{
    ui->listWidgetSel->insertItem(0,"窗口样式更改");
}

void MainFrame::stylePageInit()
{
    initTableWidget();
    initTreeWidget();
    initListWidget();
    initOther();
    initStyle();
    initTranslator();
}

void MainFrame::initTableWidget()
{
    //设置列数和列宽
//    int width = qApp->desktop()->availableGeometry().width() - 120;
    int width = QDesktopWidget().width()-120;
    ui->tableWidgetDataGrid->setColumnCount(5);
    ui->tableWidgetDataGrid->setColumnWidth(0, width * 0.06);
    ui->tableWidgetDataGrid->setColumnWidth(1, width * 0.10);
    ui->tableWidgetDataGrid->setColumnWidth(2, width * 0.06);
    ui->tableWidgetDataGrid->setColumnWidth(3, width * 0.10);
    ui->tableWidgetDataGrid->setColumnWidth(4, width * 0.15);
    ui->tableWidgetDataGrid->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "设备编号" << "设备名称" << "设备地址" << "告警内容" << "告警时间";
    ui->tableWidgetDataGrid->setHorizontalHeaderLabels(headText);
    ui->tableWidgetDataGrid->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetDataGrid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetDataGrid->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetDataGrid->setAlternatingRowColors(true);
    ui->tableWidgetDataGrid->verticalHeader()->setVisible(false);
    ui->tableWidgetDataGrid->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tableWidgetDataGrid->setRowCount(300);

    for (int i = 0; i < 300; i++) {
        ui->tableWidgetDataGrid->setRowHeight(i, 24);

        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
        QTableWidgetItem *itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        ui->tableWidgetDataGrid->setItem(i, 0, itemDeviceID);
        ui->tableWidgetDataGrid->setItem(i, 1, itemDeviceName);
        ui->tableWidgetDataGrid->setItem(i, 2, itemDeviceAddr);
        ui->tableWidgetDataGrid->setItem(i, 3, itemContent);
        ui->tableWidgetDataGrid->setItem(i, 4, itemTime);
    }
}

void MainFrame::initTreeWidget()
{
    ui->treeWidget->clear();
    ui->treeWidget->setHeaderLabel(" 树状列表控件");

    QTreeWidgetItem *group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, "父元素1");
    group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group1->setCheckState(0, Qt::PartiallyChecked);

    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem11->setText(0, "子元素1");
    subItem11->setCheckState(0, Qt::Checked);

    QTreeWidgetItem *subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem12->setText(0, "子元素2");
    subItem12->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem13->setText(0, "子元素3");
    subItem13->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *group2 = new QTreeWidgetItem(ui->treeWidget);
    group2->setText(0, "父元素2");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group2->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem21->setText(0, "子元素1");
    subItem21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *subItem211 = new QTreeWidgetItem(subItem21);
    subItem211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    subItem211->setText(0, "子子元素1");
    subItem211->setCheckState(0, Qt::Unchecked);

    ui->treeWidget->expandAll();

}
void MainFrame::initListWidget()
{
    QStringList items;
    for (int i = 1; i <= 30; i++) {
        items << QString("元素%1").arg(i);
    }

    ui->listWidget->addItems(items);
    ui->cbox1->addItems(items);
    ui->cbox2->addItems(items);

}
void MainFrame::initOther()
{
    ui->rbtn1->setChecked(true);
    ui->ck2->setChecked(true);
    ui->ck3->setCheckState(Qt::PartiallyChecked);
    ui->horizontalSlider->setValue(88);

//    ui->tab9->setStyleSheet("QPushButton{font:20pt;}");
    ui->widgetVideo->setStyleSheet("QLabel{font:20pt;}");

    ui->widgetLeft->setProperty("nav", "left");
    ui->widgetBottom->setProperty("form", "bottom");
    ui->widgetTop->setProperty("nav", "top");
//    ui->widgetVideo->setProperty("video", true);

    QList<QLabel *> labChs = ui->widgetVideo->findChildren<QLabel *>();
    foreach (QLabel *lab, labChs) {
        lab->setFocusPolicy(Qt::StrongFocus);
    }
}
void MainFrame::initStyle()
{
    //加载样式表
    QString qss;
    QFile file(":/qss/psblack.css");
    //QFile file(":/qss/flatwhite.css");
    //QFile file(":/qss/lightblue.css");
    if (file.open(QFile::ReadOnly)) {
#if 1
        //用QTextStream读取样式文件不用区分文件编码 带bom也行
        QStringList list;
        QTextStream in(&file);
        //in.setCodec("utf-8");
        while (!in.atEnd()) {
            QString line;
            in >> line;
            list << line;
        }

        qss = list.join("\n");
#else
        //用readAll读取默认支持的是ANSI格式,如果不小心用creator打开编辑过了很可能打不开
        qss = QLatin1String(file.readAll());
#endif
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(QColor(paletteColor)));
        qApp->setStyleSheet(qss);
        file.close();
    }
}
void MainFrame::initTranslator()
{}
