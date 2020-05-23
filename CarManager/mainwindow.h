#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
//
class QStandardItemModel;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_manageAction_triggered();

    void on_charAction_triggered();

    void on_quitAction_triggered();

    void on_sellFactoryComboBox_currentIndexChanged(const QString &arg1);

    void on_sellCancelBtn_clicked();

    void on_sellBrandComboBox_currentIndexChanged(const QString &arg1);

    void on_sellNumSpinBox_valueChanged(int arg1);

    void on_sellOkBtn_clicked();

    void on_factoryComboBox_currentIndexChanged(const QString &arg1);

    void on_updateBtn_clicked();

public:
    enum QDateTimeType {Time,Date,DateTime};
    QString getDateTime(QDateTimeType type);

private:
    Ui::MainWindow *ui;

    QDomDocument doc;

    bool docRead();
    bool docWrite();
    void writeXml();
    void createNodes(QDomElement &date);
    void showDailyList();

    QStandardItemModel *charModel;
    void createChartModelView();
    void showChart();

};
#endif // MAINWINDOW_H
