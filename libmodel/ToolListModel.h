#ifndef TOOLLISTMODEL_H
#define TOOLLISTMODEL_H

#include "AbstractDrillListModel.h"

class ToolListModel : public AbstractExcellonListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        DiameterRole
    };

    explicit ToolListModel(QObject* parent = nullptr)
        : AbstractExcellonListModel{parent}
    {}

    int size() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // TOOLLISTMODEL_H
