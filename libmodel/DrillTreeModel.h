#ifndef DRILLTREEMODEL_H
#define DRILLTREEMODEL_H

#include <QQmlEngine>
#include <QAbstractItemModel>
#include <QObject>

class DrillNode;
class DrillDocumentModel;

class DrillTreeModel : public QAbstractItemModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DrillDocumentModel* model READ model WRITE setModel NOTIFY modelChanged FINAL)

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
        ChildCountRole,
        IsCheckedRole,
        CheckStateRole
    };

    explicit DrillTreeModel(QObject *parent = nullptr);

    DrillDocumentModel* model() const { return documentModel_; }
    void setModel(DrillDocumentModel *newModel);

private:
    void onDocumentModelContentChanged();
    const DrillNode *itemAt(const QModelIndex &index) const;

protected:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

signals:
    void modelChanged();

private:
    DrillDocumentModel *documentModel_ = nullptr;
};

#endif // DRILLTREEMODEL_H
