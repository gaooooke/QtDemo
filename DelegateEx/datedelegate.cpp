#include "datedelegate.h"
#include <QDateTimeEdit>

DateDelegate::DateDelegate(QObject *parent)
                :QItemDelegate(parent)
{

}

QWidget * DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & /*option*/, const QModelIndex & /*index*/) const
{
    QDateTimeEdit *editor = new QDateTimeEdit(parent);
    editor->setDisplayFormat("yyyy-MM-dd");
    editor->setCalendarPopup(true);
    //安装事件过滤器，使DateDelegate能够捕获QDateTimeEdit对象的事件
    editor->installEventFilter(const_cast<DateDelegate*>(this));

    return editor;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //获取指定index数据项的数据
    //调用QModelIndex的model()函数可以获取提供index的Model对象
    //data()返回的是一个QVariant对象
    QString dateStr = index.model()->data(index).toString();
    QDate date = QDate::fromString(dateStr,Qt::ISODate);

    QDateTimeEdit *edit = static_cast<QDateTimeEdit*>(editor);
    edit->setDate(date);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateTimeEdit *edit = static_cast<QDateTimeEdit*>(editor);
    QDate date = edit->date();  //获得编辑控件中 的数据更新
    model->setData(index,QVariant(date.toString(Qt::ISODate)));
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

