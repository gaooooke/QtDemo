#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QItemDelegate>

class DateDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    DateDelegate(QObject *parent = nullptr);

    //完成创建控件的工作，创建由参数中的QModelIndex对象指定的表项数据的编辑控件，并对控件中的数据进行限定
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //设置控件显示的数据，将Model中的数据更新到Delegate中，相当于一个初始化工作
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    //更新控件区的显示
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //将Delegate中对数据的更改更新至Model中
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

};

#endif // DATEDELEGATE_H
