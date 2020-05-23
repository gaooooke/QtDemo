#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QSplitter>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDomAttr>
#include <QListWidgetItem>
#include "pieview.h"
#include <QStandardItemModel>
#include <QTableView>

//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(750,500);
    ui->stackedWidget->setCurrentIndex(0);

    QSqlQueryModel *factoryModel = new QSqlQueryModel(this);
    factoryModel->setQuery("select name from factory");
    ui->sellFactoryComboBox->setModel(factoryModel);

    showDailyList();

    ui->factoryComboBox->setModel(factoryModel);
    createChartModelView();

//    QSplitter *splitter = new QSplitter(ui->managePage);
//    splitter->resize(700,360);
//    splitter->move(0,50);
//    splitter->addWidget(ui->toolBox);
//    splitter->addWidget(ui->dailyList);
//    splitter->setStretchFactor(0,1);
//    splitter->setStretchFactor(1,1);

    setWindowTitle("汽车销售管理系统");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_manageAction_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_charAction_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_quitAction_triggered()
{
    close();
}

void MainWindow::on_sellFactoryComboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "请选择厂家")  on_sellCancelBtn_clicked();
    else
    {
        ui->sellBrandComboBox->setEnabled(true);
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(QString("select name from brand where factory='%1'").arg(arg1));
        ui->sellBrandComboBox->setModel(model);
        ui->sellCancelBtn->setEnabled(true);
    }

}

void MainWindow::on_sellBrandComboBox_currentIndexChanged(const QString &arg1)
{
    ui->sellNumSpinBox->setValue(0);
    ui->sellNumSpinBox->setEnabled(false);
    ui->sellSumLineEdit->clear();
    ui->sellSumLineEdit->setEnabled(false);
    ui->sellOkBtn->setEnabled(false);

    QSqlQuery query;
    query.exec(QString("select price from brand where name='%1' and factory='%2'").arg(arg1).arg(ui->sellFactoryComboBox->currentText()));
    query.next();
    ui->sellPriceLineEdit->setEnabled(true);
    ui->sellPriceLineEdit->setReadOnly(true);
    ui->sellPriceLineEdit->setText(query.value(0).toString());

    query.exec(QString("select price from brand where name = '%1' and factory='%2'").arg(arg1).arg(ui->sellFactoryComboBox->currentText()));
    query.next();
    ui->sellPriceLineEdit->setEnabled(true);
    ui->sellPriceLineEdit->setReadOnly(true);
    ui->sellPriceLineEdit->setText(query.value(0).toString());

    query.exec(QString("select last from brand where name='%1' and factory='%2'").arg(arg1).arg(ui->sellFactoryComboBox->currentText()));
    query.next();
    int num = query.value(0).toInt();
    if(num == 0)
        QMessageBox::information(this,"提示","该品牌汽车已经售完",QMessageBox::Ok);
    else
    {
        ui->sellNumSpinBox->setEnabled(true);
        ui->sellNumSpinBox->setMaximum(num);
        ui->sellLastNumLabel->setText(tr("剩余数量：%1").arg(num));
        ui->sellLastNumLabel->setVisible(true);
    }
}

void MainWindow::on_sellCancelBtn_clicked()
{
    ui->sellFactoryComboBox->setCurrentIndex(0);
    ui->sellBrandComboBox->clear();
}

void MainWindow::on_sellNumSpinBox_valueChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->sellSumLineEdit->clear();
        ui->sellSumLineEdit->setEnabled(false);
        ui->sellOkBtn->setEnabled(false);
    }
    else
    {
        ui->sellSumLineEdit->setEnabled(true);
        ui->sellSumLineEdit->setReadOnly(true);
        qreal sum = arg1*ui->sellPriceLineEdit->text().toInt();
        ui->sellSumLineEdit->setText(QString::number(sum));
        ui->sellOkBtn->setEnabled(true);
    }
}

void MainWindow::on_sellOkBtn_clicked()
{
    QString factory = ui->sellFactoryComboBox->currentText();
    QString name = ui->sellBrandComboBox->currentText();
    int value = ui->sellNumSpinBox->value();

    int last = ui->sellNumSpinBox->maximum()-value;

    QSqlQuery   query;
    query.exec(QString("select sell from brand where name = '%1' and factory ='%2'")
               .arg(name)
               .arg(factory));
    query.next();

    int sell =query.value(0).toInt()+value;

    //事务操作
    QSqlDatabase::database().transaction();
    bool rtn = query.exec(QString("update brand set sell=%1,last=%2 where name='%3' and factory='%4'")
                          .arg(sell)
                          .arg(last)
                          .arg(name)
                          .arg(factory));
    if(rtn)
    {
        QSqlDatabase::database().commit();
        QMessageBox::information(this,"提示","购车成功",QMessageBox::Ok);
        writeXml();
        showDailyList();
        on_sellCancelBtn_clicked();
    }
    else
    {
        QSqlDatabase::database().rollback();
    }
}

QString MainWindow::getDateTime(QDateTimeType type)
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString date = datetime.toString("yyyy-MM-dd");
    QString time = datetime.toString("hh:mm");
    QString dateAndTime = datetime.toString("yyyy-MM-dd dddd hh:mm");
    if(type == Date) return date;
    else if(type == Time) return time;
    else return dateAndTime;
}

bool MainWindow::docRead()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::ReadOnly))
        return false;
    if(!doc.setContent(&file))
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool MainWindow::docWrite()
{
    QFile file("data.xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

//    QDomDocument doc;

//    QDomElement root = doc.createElement(QString("日销售清单"));
//    doc.appendChild(root);

    QTextStream out(&file);
    doc.save(out,4);
    file.close();

    return true;
}

void MainWindow::writeXml()
{
    if(docRead())
    {
        QString currentDate = getDateTime(Date);
        QDomElement root = doc.documentElement();

        if(!root.hasChildNodes())
        {
            QDomElement date = doc.createElement(QString("日期"));
            QDomAttr curDate = doc.createAttribute("date");
            curDate.setValue(currentDate);
            date.setAttributeNode(curDate);
            root.appendChild(date);
            createNodes(date);
        }
        else
        {
            QDomElement date = root.lastChild().toElement();
            if(date.attribute("date") == currentDate)
                createNodes(date);
            else
            {
                QDomElement date = doc.createElement(QString("日期"));
                QDomAttr curDate = doc.createAttribute("date");
                curDate.setValue(currentDate);
                date.setAttributeNode(curDate);
                root.appendChild(date);
                createNodes(date);
            }
        }
        docWrite();
    }
}

void MainWindow::createNodes(QDomElement &date)
{
    QDomElement time = doc.createElement(QString("时间"));
    QDomAttr curTime = doc.createAttribute("time");
    curTime.setValue(getDateTime(Time));
    time.setAttributeNode(curTime);
    date.appendChild(time);

    QDomElement factory = doc.createElement(QString("厂家"));
    QDomElement brand = doc.createElement(QString("品牌"));
    QDomElement price = doc.createElement(QString("报价"));
    QDomElement num = doc.createElement(QString("数量"));
    QDomElement sum = doc.createElement(QString("金额"));

    QDomText text;
    text = doc.createTextNode(QString("%1").arg(ui->sellFactoryComboBox->currentText()));
    factory.appendChild(text);

    text = doc.createTextNode(QString("&1").arg(ui->sellBrandComboBox->currentText()));
    brand.appendChild(text);

    text = doc.createTextNode(QString("%1").arg(ui->sellPriceLineEdit->text()));
    price.appendChild(text);

    text = doc.createTextNode(QString("%1").arg(ui->sellNumSpinBox->value()));
    num.appendChild(text);

    text=doc.createTextNode(QString("%1").arg(ui->sellSumLineEdit->text()));
    sum.appendChild(text);

    time.appendChild(factory);
    time.appendChild(brand);
    time.appendChild(price);
    time.appendChild(num);
    time.appendChild(sum);
}

void MainWindow::showDailyList()
{
    ui->dailyList->clear();
    if(docRead())
    {
        QDomElement root = doc.documentElement();
        QString title = root.tagName();
        QListWidgetItem *titleItem = new QListWidgetItem;
        titleItem->setText(QString("----------%1-----------").arg(title));
        titleItem->setTextAlignment(Qt::AlignCenter);
        ui->dailyList->addItem(titleItem);
        if(root.hasChildNodes())
        {
            QString currentDate = getDateTime(Date);
            QDomElement dateElement = root.lastChild().toElement();
            QString date = dateElement.attribute("date");
            if(date == currentDate)
            {
                ui->dailyList->addItem("");
                ui->dailyList->addItem(QString("日期:%1").arg(date));
                ui->dailyList->addItem("");
                QDomNodeList children = dateElement.childNodes();

                for (int i=0;i<children.count();i++) {
                    QDomNode node = children.at(i);
                    QString time = node.toElement().attribute("time");
                    QDomNodeList list = node.childNodes();
                    QString factory = list.at(0).toElement().text();
                    QString brand = list.at(1).toElement().text();
                    QString price = list.at(2).toElement().text();
                    QString num = list.at(3).toElement().text();
                    QString sum = list.at(4).toElement().text();

                    QString str = time+"出售"+brand+factory+" "+num+"辆, "+"成交价:"+price+"万,共"+sum+"万元";
                    QListWidgetItem *tempItem = new QListWidgetItem;
                    tempItem->setText("******************************");
                    tempItem->setTextAlignment(Qt::AlignCenter);
                    ui->dailyList->addItem(tempItem);
                    ui->dailyList->addItem(str);
                }
            }
        }
    }
}

void MainWindow::createChartModelView()
{
    charModel = new QStandardItemModel(this);
    charModel->setColumnCount(2);
    charModel->setHeaderData(0,Qt::Horizontal,"品牌");
    charModel->setHeaderData(1,Qt::Horizontal,"销售数量");

    QSplitter *splitter = new QSplitter(ui->chartPage);
    splitter->resize(700,320);
    splitter->move(0,80);
    QTableView *table = new QTableView;
    PieView *pieChart = new PieView;
    splitter->addWidget(table);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0,1);
    splitter->setStretchFactor(1,2);

    table->setModel(charModel);
    pieChart->setModel(charModel);

    QItemSelectionModel *selectionModel = new QItemSelectionModel(charModel);
    table->setSelectionModel(selectionModel);
    pieChart->setSelectionModel(selectionModel);
}

void MainWindow::showChart()
{
    QSqlQuery query;
    query.exec(QString("select name,sell from brand where factory ='%1'").arg(ui->factoryComboBox->currentText()));
    charModel->removeRows(0,charModel->rowCount(QModelIndex()),QModelIndex());

    int row = 0;

    while(query.next())
    {
        int r = qrand()%256;
        int g = qrand()%256;
        int b = qrand()%256;

        charModel->insertRows(row,1,QModelIndex());
        charModel->setData(charModel->index(row,0,QModelIndex()),query.value(0).toString());
        charModel->setData(charModel->index(row,1,QModelIndex()),query.value(1).toString());
        charModel->setData(charModel->index(row,0,QModelIndex()),QColor(r,g,b),Qt::DecorationRole);

        row++;
    }
}

void MainWindow::on_factoryComboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1!="请选择厂家")
        showChart();
}

void MainWindow::on_updateBtn_clicked()
{
    if(ui->factoryComboBox->currentText()!="请选择厂家")
        showChart();
}
