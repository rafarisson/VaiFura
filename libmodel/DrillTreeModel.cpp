#include "DrillDocument.h"
#include "DrillTreeItem.h"
#include "DrillTreeModel.h"


DrillTreeModel::DrillTreeModel(QObject *parent)
    : QAbstractItemModel{parent}
    , rootItem_{new DrillTreeItem({}, nullptr)}
{}

DrillTreeModel::~DrillTreeModel()
{
    delete rootItem_;
}

void DrillTreeModel::setModel(const DrillDocument *model) {
    beginResetModel();

    for (const Tool& tool : model->tools()) {
        auto *toolItem = new DrillTreeItem(QVariant::fromValue(tool), rootItem_);
        rootItem_->appendChild(toolItem);

        for (const Hole& drill : model->holes()) {
            if (drill.toolId == tool.id) {
                toolItem->appendChild(
                    new DrillTreeItem(QVariant::fromValue(drill), toolItem)
                    );
            }
        }
    }

    endResetModel();
}

DrillTreeItem *DrillTreeModel::itemAt(const QModelIndex &index) const
{
    if (index.isValid()) {
        auto *item = static_cast<DrillTreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem_;
}

QModelIndex DrillTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return {};

    DrillTreeItem *parentItem = itemAt(parent);
    DrillTreeItem *childItem = parentItem->child(row);

    if (!childItem)
        return {};

    return createIndex(row, column, childItem);
}

QModelIndex DrillTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return {};

    DrillTreeItem *childItem = itemAt(child);
    DrillTreeItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == rootItem_)
        return {};

    return createIndex(parentItem->row(), 0, parentItem);
}

int DrillTreeModel::rowCount(const QModelIndex &parent) const
{
    return itemAt(parent)->childCount();
}

int DrillTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant DrillTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    auto *item = static_cast<DrillTreeItem*>(index.internalPointer());

    switch (role) {
    case ChildCountRole: return item->childCount();
    }

    if (item->data().canConvert<Tool>()) {
        Tool t = item->data().value<Tool>();
        switch (role) {
        case ItemTypeRole: return ToolType;
        case DiameterRole: return t.mm;
        }
    }

    if (item->data().canConvert<Hole>()) {
        Hole d = item->data().value<Hole>();
        switch (role) {
        case ItemTypeRole: return DrillType;
        case XRole: return d.x;
        case YRole: return d.y;
        }
    }

    return {};
}

// QVariant DrillTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
// {
//     return {};
// }

QHash<int, QByteArray> DrillTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemTypeRole] = "itemType";
    roles[DiameterRole] = "diameter";
    roles[XRole] = "posX";
    roles[YRole] = "posY";
    roles[ChildCountRole] = "childCount";
    return roles;
}


