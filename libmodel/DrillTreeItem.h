#ifndef DRILLTREEITEM_H
#define DRILLTREEITEM_H

#include <QVector>
#include <QVariant>

class DrillTreeItem
{
public:
    explicit DrillTreeItem(QVariant data, DrillTreeItem *parent = nullptr);
    ~DrillTreeItem();

    void appendChild(DrillTreeItem *child);
    DrillTreeItem *child(int row);
    int childCount() const { return children_.size(); }
    QVariant data() const { return data_; }
    int row() const;
    DrillTreeItem * parent() const { return parent_; }

private:
    QVector<DrillTreeItem*> children_;
    QVariant data_;
    DrillTreeItem *parent_;
};

#endif // DRILLTREEITEM_H
