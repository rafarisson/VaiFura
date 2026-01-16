#include "HoleListModel.h"
#include "DrillDocument.h"

HoleListModel::HoleListModel(QObject *parent)
    : AbstractToolHoleListModel{parent}
{}

int HoleListModel::size() const
{
    return isValid() ? doc_->holes().size() : 0;
}

QVariant HoleListModel::data(const QModelIndex &index, int role) const
{
    if (!isValid())
        return {};
    if (!index.isValid() || index.row() < 0 || index.row() >= size())
        return {};

    const auto &d = doc_->holes()[index.row()];

    switch (role) {
    case XRole: return d.x;
    case YRole: return d.y;
    case ToolRole: return d.toolId;
    }

    return {};
}

QHash<int, QByteArray> HoleListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[XRole] = "posX";
    roles[YRole] = "posY";
    roles[ToolRole] = "toolId";
    return roles;
}
