#ifndef HOLELISTMODEL_H
#define HOLELISTMODEL_H

#include <QQmlEngine>
#include "AbstractToolHoleListModel.h"

class HoleListModel : public AbstractToolHoleListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        XRole = Qt::UserRole + 1,
        YRole,
        ToolRole
    };

    explicit HoleListModel(QObject* parent = nullptr);

    int size() const override;

protected:
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
};

#endif // HOLELISTMODEL_H
