#include "ToolListModel.h"
#include "DrillModel.h"

int ToolListModel::size() const
{
    return isValid() ? model()->tools().size() : 0;
}

QVariant ToolListModel::data(const QModelIndex &index, int role) const
{
    if (!isValid())
        return {};
    if (!index.isValid() || index.row() < 0 || index.row() >= size())
        return {};

    const auto &t = model()->tools()[index.row()];

    switch (role) {
    case IdRole: return t.id;
    case DiameterRole: return t.mm;
    }

    return {};
}

QHash<int, QByteArray> ToolListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[DiameterRole] = "diameter";
    return roles;
}
