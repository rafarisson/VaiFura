#ifndef DRILLLISTMODEL_H
#define DRILLLISTMODEL_H

#include "AbstractDrillListModel.h"

class DrillListModel : public AbstractExcellonListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        XRole = Qt::UserRole + 1,
        YRole,
        ToolRole
    };

    explicit DrillListModel(QObject* parent = nullptr)
        : AbstractExcellonListModel{parent}
    {}

    int size() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // DRILLLISTMODEL_H
