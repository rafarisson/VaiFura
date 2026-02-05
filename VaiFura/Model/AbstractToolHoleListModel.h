#ifndef ABSTRACTTOOLHOLELISTMODEL_H
#define ABSTRACTTOOLHOLELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include "DrillDocumentModel.h"

class AbstractToolHoleListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(DrillDocumentModel* model READ model WRITE setModel NOTIFY modelChanged FINAL)

public:
    explicit AbstractToolHoleListModel(QObject* parent = nullptr)
        : QAbstractListModel{parent}
    {}
    virtual ~AbstractToolHoleListModel() = default;

    bool isValid() const {
        return documentModel_ && documentModel_->document();
    }

    virtual int size() const = 0;

    DrillDocumentModel *model() const { return documentModel_; }
    void setModel(DrillDocumentModel *newModel) {
        if (documentModel_ == newModel)
            return;

        if (documentModel_)
            disconnect(documentModel_, nullptr, this, nullptr);

        beginResetModel();
        documentModel_ = newModel;
        endResetModel();

        emit modelChanged();

        if (documentModel_)
            connect(documentModel_, &DrillDocumentModel::documentContentChanged, this, &AbstractToolHoleListModel::onDocumentModelContentChanged);
    }

protected:
    int rowCount(const QModelIndex &index) const override {
        return isValid() ? size() : 0;
    }

signals:
    void modelChanged();

private:
    void onDocumentModelContentChanged() {
        beginResetModel();
        endResetModel();
    }

    DrillDocumentModel* documentModel_ = nullptr;
};

#endif // ABSTRACTTOOLHOLELISTMODEL_H
