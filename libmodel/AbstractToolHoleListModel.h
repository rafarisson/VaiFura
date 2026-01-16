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

    void setModel(const DrillDocument *model) {
        beginResetModel();
        doc_ = model;
        endResetModel();
    }

protected:
    int rowCount(const QModelIndex &index) const override {
        return isValid() ? size() : 0;
    }

    const DrillDocument* doc_ = nullptr;
};

#endif // ABSTRACTTOOLHOLELISTMODEL_H
