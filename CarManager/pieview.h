#ifndef PIEVIEW_H
#define PIEVIEW_H

#include <QObject>
#include <QWidget>
#include <QAbstractItemView>
//
class PieView : public QAbstractItemView
{
    Q_OBJECT
public:
    explicit PieView(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) override;

    //为selections赋初值
    void setSelectionModel(QItemSelectionModel *selectionModel) override;
    QRegion itemRegion(QModelIndex index);

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
    QModelIndex indexAt(const QPoint &point) const override;
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    int horizontalOffset() const override;
    int verticalOffset() const override;
    bool isIndexHidden(const QModelIndex &index) const override;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
    QRegion visualRegionForSelection(const QItemSelection &selection) const override;

signals:

private:
    QItemSelectionModel *selections;
    QList<QRegion> RegionList;

};

#endif // PIEVIEW_H
