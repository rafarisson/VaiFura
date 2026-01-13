#ifndef ABSTRACTDRILLLISTMODEL_H
#define ABSTRACTDRILLLISTMODEL_H

#include <QQmlEngine>
#include <QAbstractListModel>
#include <QObject>

#include "DrillModel.h"

class AbstractDrillListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AbstractDrillListModel(QObject* parent = nullptr)
        : QAbstractListModel{parent}
    {}
    virtual ~AbstractDrillListModel() = default;

    bool isValid() const {
        return model_ != nullptr;
    }

    virtual int size() const = 0;

    const DrillModel *model() const {
        return model_;
    }

    void setModel(const DrillModel *model) {
        beginResetModel();
        model_ = model;
        endResetModel();
        emit modelChanged();
    }

protected:
    int rowCount(const QModelIndex &index) const override {
        return size();
    }

signals:
    void modelChanged();

private:
    const DrillModel* model_ = nullptr;
};

#endif // ABSTRACTDRILLLISTMODEL_H
