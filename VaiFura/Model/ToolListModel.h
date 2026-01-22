#ifndef TOOLLISTMODEL_H
#define TOOLLISTMODEL_H

#include <QQmlEngine>
#include "AbstractToolHoleListModel.h"

class ToolListModel : public AbstractToolHoleListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        DiameterRole
    };

    explicit ToolListModel(QObject* parent = nullptr);

    int size() const override;

protected:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // TOOLLISTMODEL_H
