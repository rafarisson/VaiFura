#include "DrillListModel.h"
#include "DrillModel.h"

int DrillListModel::size() const
{
    return isValid() ? model()->drills().size() : 0;
}

QVariant DrillListModel::data(const QModelIndex &index, int role) const
{
    if (!isValid())
        return {};
    if (!index.isValid() || index.row() < 0 || index.row() >= size())
        return {};

    const auto &d = model()->drills()[index.row()];

    switch (role) {
    case XRole: return d.x;
    case YRole: return d.y;
    case ToolRole: return d.toolId;
    }

    return {};
}

QHash<int, QByteArray> DrillListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[XRole] = "posX";
    roles[YRole] = "posY";
    roles[ToolRole] = "toolId";
    return roles;
}
