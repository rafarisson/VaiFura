#include "ExportSettingsListModel.h"
#include "ExportSettingsRepository.h"

ExportSettingsListModel::ExportSettingsListModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

void ExportSettingsListModel::load(const QString &fileName)
{
    beginResetModel();
    ExportSettingsRepository::load(fileName, &settings_);
    endResetModel();
    emit sizeChanged();
}

void ExportSettingsListModel::save(const QString &fileName)
{

}

int ExportSettingsListModel::rowCount(const QModelIndex &parent) const
{
    return size();
}

QVariant ExportSettingsListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= size())
        return {};

    const ExportSettings &s = settings_.at(index.row());

    switch (role) {
    case KeyRole: return s.key;
    case LabelRole: return s.label;
    case DescriptionRole: return s.description;
    case UnitRole: return s.unit;
    case ValueRole: return s.value;
    case TypeRole: return s.type;
    }

    return {};
}

bool ExportSettingsListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || index.row() < 0 || index.row() >= size())
        return false;
    if (role != ValueRole)
        return false;

    ExportSettings &s = settings_[index.row()];
    if (s.value == value)
        return false;

    s.value = value;
    emit dataChanged(index, index, { role });

    qDebug() << "set" << role << value;

    return true;
}

QHash<int, QByteArray> ExportSettingsListModel::roleNames() const
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
