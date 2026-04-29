#ifndef ABSTRACTOPTIMIZATIONPLAN_H
#define ABSTRACTOPTIMIZATIONPLAN_H

#include <QVector>
#include <QPointF>

#include "DrillNode.h"

class DrillTransform;

struct HoleRef {
    const DrillNode* node = nullptr;
    QPointF pos;
};

class AbstractOptimizationPlan
{
public:
    virtual ~AbstractOptimizationPlan() = default;

    virtual QString name() const = 0;
    virtual void optimize(const DrillNode *root, const DrillTransform *transform) = 0;

    const QVector<HoleRef> &holes() const { return holes_; }
    const QVector<int> &order() const { return order_; }
    bool isEmpty() const { return holes_.isEmpty(); }

protected:
    double distance(const QPointF &a, const QPointF &b) const;
    void build(const DrillNode *root);

    QVector<int> order_;

private:
    QVector<HoleRef> holes_;
};

#endif // ABSTRACTOPTIMIZATIONPLAN_H
