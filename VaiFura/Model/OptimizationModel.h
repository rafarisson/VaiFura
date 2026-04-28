#ifndef OPTIMIZATIONMODEL_H
#define OPTIMIZATIONMODEL_H

#include <QObject>
#include <QQmlEngine>

#include "AbstractOptimizationPlan.h"

class DrillDocument;
class DrillTransformModel;

class OptimizationModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit OptimizationModel(QObject *parent = nullptr);

    const AbstractOptimizationPlan *optimizationPlan() const { return plan_; }
    void setOptimizationPlan(AbstractOptimizationPlan *plan);

    void optimize(const DrillNode* root, const DrillTransformModel *transformModel = nullptr);
    void generateOptimizedDrillDocument(DrillDocument &out) const;

signals:
    void optimizationPlanChanged();

private:
    AbstractOptimizationPlan *plan_ = nullptr;
};

#endif // OPTIMIZATIONMODEL_H
