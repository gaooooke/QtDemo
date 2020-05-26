#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainFrame; }
QT_END_NAMESPACE

class MainFrame : public QMainWindow
{
    Q_OBJECT

public:
    MainFrame(QWidget *parent = nullptr);
    ~MainFrame();

private:
    Ui::MainFrame *ui;
};
#endif // MAINFRAME_H
