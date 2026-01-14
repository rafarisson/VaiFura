#include "DrillTreeModel.h"
#include "DrillDocument.h"
#include "DrillTreeDocument.h"
#include "DrillTreeNode.h"

DrillTreeModel::DrillTreeModel(QObject *parent)
    : QAbstractItemModel{parent}
    , treeDoc_{new DrillTreeDocument()}
{}

void DrillTreeModel::setDocument(const DrillTreeDocument *doc) {
    beginResetModel();
    treeDoc_ = doc;
    endResetModel();
}

DrillTreeNode *DrillTreeModel::itemAt(const QModelIndex &index) const
{
    if (index.isValid()) {
        auto *item = static_cast<DrillTreeNode*>(index.internalPointer());
        if (item)
            return item;
    }
    return treeDoc_->root();
}

// QModelIndex DrillTreeModel::indexFromNode(DrillTreeNode *node) const
// {
//     if (!node || node == treeDoc_->root())
//         return {};

//     return createIndex(node->row(), 0, node);
// }

QModelIndex DrillTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return {};

    auto *parentItem = itemAt(parent);
    auto *childItem = parentItem->child(row);

    if (!childItem)
        return {};

    return createIndex(row, column, childItem);
}

QModelIndex DrillTreeModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return {};

    auto *childItem = itemAt(child);
    auto *parentItem = childItem->parent();

    if (!parentItem || parentItem == treeDoc_->root())
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

    auto *item = itemAt(index);

    switch (role) {
    case ChildCountRole: return item->childCount();
    case IsCheckedRole: return item->isChecked();
    }

    if (item->type() == DrillTreeNode::Type::IsTool) {
        switch (role) {
        case Qt::DisplayRole:
        case ItemTypeRole: return ToolType;
        case DiameterRole: return item->tool()->mm;
        }
    }

    if (item->type() == DrillTreeNode::Type::IsHole) {
        switch (role) {
        case Qt::DisplayRole:
        case ItemTypeRole: return DrillType;
        case XRole: return item->hole()->x;
        case YRole: return item->hole()->y;
        }
    }

    return {};
}

bool DrillTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData" << index;
    if (!index.isValid())
        return false;

    auto *item = itemAt(index);
    qDebug() << "item" << index;
    if (!item)
        return false;

    qDebug() << "setData" << role;
    if (role != IsCheckedRole && role != Qt::CheckStateRole)
        return false;

    bool newChecked = value.toBool();
    qDebug() << newChecked << item->isChecked();
    if (!item->setChecked(newChecked))
        return false;

    emit dataChanged(index, index, { role });

    // if (item->childCount() && newState != Qt::PartiallyChecked) {
    //     emit dataChanged(indexFromNode(item->children().first()),
    //                      indexFromNode(item->children().last()),
    //                      { role });
    // }

    // if (role == CheckedRole || role == Qt::CheckStateRole) {
    //     bool newState = (value.toInt() == Qt::Checked) || value.toBool();
    //     if (item->setChecked(newState)) {
    //         qDebug() << "update" << newState;
    //         emit dataChanged(index, index, { role });
    //     }
    // }

    return true;
}

QHash<int, QByteArray> DrillTreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ItemTypeRole] = "type";
    roles[DiameterRole] = "diameter";
    roles[XRole] = "posX";
    roles[YRole] = "posY";
    roles[ChildCountRole] = "childCount";
    roles[IsCheckedRole] = "isChecked";
    return roles;
}


