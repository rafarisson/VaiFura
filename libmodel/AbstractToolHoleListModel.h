#ifndef ABSTRACTTOOLHOLELISTMODEL_H
#define ABSTRACTTOOLHOLELISTMODEL_H

#include <QAbstractListModel>
#include <QObject>

#include "DrillDocument.h"

class AbstractToolHoleListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AbstractToolHoleListModel(QObject* parent = nullptr)
        : QAbstractListModel{parent}
    {}
    virtual ~AbstractToolHoleListModel() = default;

    bool isValid() const {
        return doc_ != nullptr;
    }

    virtual int size() const = 0;

    const DrillDocument *document() const {
        return doc_;
    }

    void setDocument(const DrillDocument *model) {
        beginResetModel();
        doc_ = model;
        endResetModel();
    }

protected:
    int rowCount(const QModelIndex &index) const override {
        return isValid() ? size() : 0;
    }

private:
    const DrillDocument* doc_ = nullptr;
};

#endif // ABSTRACTTOOLHOLELISTMODEL_H
