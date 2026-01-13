#include "DrillTreeItem.h"

DrillTreeItem::DrillTreeItem(QVariant data, DrillTreeItem *parent)
    : data_{data}
    , parent_{parent}
{   
}

DrillTreeItem::~DrillTreeItem()
{
    qDeleteAll(children_);
    children_.clear();
}

void DrillTreeItem::appendChild(DrillTreeItem *child)
{
    children_.append(child);
}

DrillTreeItem *DrillTreeItem::child(int row)
{
    return children_.value(row);
}

int DrillTreeItem::row() const
{
    if (!parent_)
        return 0;

    return parent_->children_.indexOf(this);
}
