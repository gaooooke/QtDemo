#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelection>
#include "addresswidget.h"
#include "adddialog.h"

//
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
      MainWindow();

private slots:
      void updateActions(const QItemSelection &selection);
      void openFile();
      void saveFile();

private:
      void createMenus();

      AddressWidget *addressWidget;
      AddDialog *addDlg;
      QAction *editAct;
      QAction *removeAct;
      QAction *addAct;
};
#endif // MAINWINDOW_H
