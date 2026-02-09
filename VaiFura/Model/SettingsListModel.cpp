#include "SettingsListModel.h"

SettingsListModel::SettingsListModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

void SettingsListModel::setSettings(const QVector<Settings> &newSettings)
{
    beginResetModel();
    settings_ = newSettings;
    endResetModel();
}

int SettingsListModel::rowCount(const QModelIndex &parent) const
{
    return size();
}

QVariant SettingsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= size())
        return {};

    const Settings &s = settings_.at(index.row());

    switch (role) {
    case KeyRole: return s.key;
    case LabelRole: return tr(qPrintable(s.label));
    case DescriptionRole: return tr(qPrintable(s.description));
    case UnitRole: return s.unit;
    case ValueRole: return s.value;
    case TypeRole: return s.type;
    }

    return {};
}

bool SettingsListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= size())
        return false;
    if (role != ValueRole)
        return false;

    Settings &s = settings_[index.row()];
    if (s.value == value)
        return false;

    s.value = value;
    emit dataChanged(index, index, { role });

    return true;
}

QHash<int, QByteArray> SettingsListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[LabelRole] = "label";
    roles[DescriptionRole] = "description";
    roles[UnitRole] = "unit";
    roles[ValueRole] = "value";
    roles[TypeRole] = "type";
    return roles;
}
