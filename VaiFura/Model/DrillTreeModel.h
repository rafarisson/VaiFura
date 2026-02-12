#ifndef DRILLTREEMODEL_H
#define DRILLTREEMODEL_H

#include <QQmlEngine>
#include <QAbstractItemModel>
#include <QObject>

class DrillNode;
class DrillDocumentModel;
class DrillTransformModel;

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
        DocumentModelRole = Qt::UserRole + 1,
        TransformModelRole,
        ItemTypeRole,
        DiameterRole,
        XRole,
        YRole,
        ChildCountRole,
        IsCheckedRole,
        CheckStateRole
    };
    Q_ENUM(DrillTreeRoleNames)

    explicit DrillTreeModel(QObject *parent = nullptr);

    DrillDocumentModel* model() const { return documentModel_; }
    DrillTransformModel* transformModel() const { return transformModel_; }
    void setModel(DrillDocumentModel *doc, DrillTransformModel *transform = nullptr);

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
    DrillTransformModel *transformModel_ = nullptr;
};

#endif // DRILLTREEMODEL_H
