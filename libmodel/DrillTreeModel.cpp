#include "DrillTreeModel.h"
#include "DrillDocumentModel.h"
#include "DrillDocument.h"
#include "DrillNode.h"

DrillTreeModel::DrillTreeModel(QObject *parent)
    : QAbstractItemModel{parent}
{}

void DrillTreeModel::setModel(DrillDocumentModel *newModel) {
    if (documentModel_ == newModel)
        return;

    if (documentModel_)
        disconnect(documentModel_, nullptr, this, nullptr);

    beginResetModel();
    documentModel_ = newModel;
    endResetModel();

    emit modelChanged();

    if (documentModel_)
        connect(documentModel_, &DrillDocumentModel::documentContentChanged, this, &DrillTreeModel::onDocumentModelContentChanged);
}

void DrillTreeModel::onDocumentModelContentChanged()
{
    beginResetModel();
    endResetModel();
}

const DrillNode *DrillTreeModel::itemAt(const QModelIndex &index) const
{
    if (!documentModel_ || !documentModel_->document()->root())
        return nullptr;

    if (index.isValid()) {
        auto *item = static_cast<DrillNode*>(index.internalPointer());
        if (item)
            return item;
    }

    return documentModel_->document()->root();
}

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
    if (!documentModel_ || !documentModel_->document()->root() || !child.isValid())
        return {};

    auto *childItem = itemAt(child);
    auto *parentItem = childItem->parent();

    if (!parentItem || parentItem == documentModel_->document()->root())
        return {};

    return createIndex(parentItem->row(), 0, parentItem);
}

int DrillTreeModel::rowCount(const QModelIndex &parent) const
{
    return documentModel_ && documentModel_->document()->root() ? itemAt(parent)->childCount() : 0;
}

int DrillTreeModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant DrillTreeModel::data(const QModelIndex &index, int role) const
{
    if (!documentModel_ || !documentModel_->document()->root() || !index.isValid())
        return {};

    auto *item = itemAt(index);
    if (!item)
        return {};

    switch (role) {
    case ChildCountRole: return item->childCount();
    case IsCheckedRole: return item->isChecked();
    case CheckStateRole: return item->checkState();
    }

    if (item->type() == DrillNode::Type::IsTool) {
        switch (role) {
        case Qt::DisplayRole:
        case ItemTypeRole: return ToolType;
        case DiameterRole: return item->tool()->mm;
        }
    }

    if (item->type() == DrillNode::Type::IsHole) {
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
    if (!documentModel_ || !documentModel_->document()->root() || !index.isValid() || role != CheckStateRole)
        return false;

    // auto *item = (DrillNode*)itemAt(index);
    auto *item = itemAt(index);
    if (!item || item == documentModel_->document()->root())
        return false;

    // Qt::CheckState newState = value.value<Qt::CheckState>();
    // if (!item->setCheckState(newState))
    //     return false;
    if (!documentModel_->setCheckState(item, value.value<Qt::CheckState>()))
        return false;

    emit dataChanged(index, index, { role });

    if (item->childCount()) {
        QModelIndex parentIndex = DrillTreeModel::index(item->row(), 0, QModelIndex());
        QModelIndex first = DrillTreeModel::index(0, 0, parentIndex);
        QModelIndex last = DrillTreeModel::index(item->childCount() - 1, 0, parentIndex);
        emit dataChanged(first, last, { role });
    }

    QModelIndex recursiveParentIndex = parent(index);
    while (recursiveParentIndex.isValid()) {
        emit dataChanged(recursiveParentIndex, recursiveParentIndex, { role });
        recursiveParentIndex = parent(recursiveParentIndex);
    }

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
    roles[CheckStateRole] = "checkState";
    return roles;
}


