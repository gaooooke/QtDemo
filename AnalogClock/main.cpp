#include "mainwindow.h"
#include "analogclockwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnalogClockWindow w;
    w.show();
    return a.exec();
}
