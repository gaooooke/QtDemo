#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

//
class AddDialog : public QDialog
{
    Q_OBJECT

public:
      AddDialog(QWidget *parent = nullptr);

      QString name() const;
      QString address() const;
      void editAddress(const QString &name, const QString &address);

private:
      QLineEdit *nameText;
      QTextEdit *addressText;
};

#endif // ADDDIALOG_H
