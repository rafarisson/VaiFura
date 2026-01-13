#ifndef DRILLTREEMODEL_H
#define DRILLTREEMODEL_H

#include <QQmlEngine>
#include <QAbstractItemModel>
#include <QObject>

class DrillModel;
class DrillTreeItem;

class DrillTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum DrillTreeItemType {
        ToolType,
        DrillType
    };
    Q_ENUM(DrillTreeItemType)

    enum DrillTreeRoleNames {
        ItemTypeRole = Qt::UserRole + 1,
        DiameterRole,
        XRole,
        YRole,
        ChildCountRole
    };

    explicit DrillTreeModel(QObject *parent = nullptr);
    ~DrillTreeModel();
    void setModel(const DrillModel *model);

private:
    DrillTreeItem *itemAt(const QModelIndex &index) const;

protected:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    // QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    DrillTreeItem *rootItem_;
};

#endif // DRILLTREEMODEL_H
