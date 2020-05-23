#ifndef NEWADDRESSTAB_H
#define NEWADDRESSTAB_H

#include <QWidget>

//
class NewAddressTab : public QWidget
{
    Q_OBJECT

public:
      NewAddressTab(QWidget *parent = nullptr);

public slots:
      void addEntry();

signals:
      void sendDetails(const QString &name, const QString &address);

};

#endif // NEWADDRESSTAB_H
