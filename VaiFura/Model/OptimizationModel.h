#ifndef OPTIMIZATIONMODEL_H
#define OPTIMIZATIONMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QScopedPointer>

#include "AbstractOptimizationPlan.h"

class DrillDocument;
class DrillTransformModel;

class OptimizationModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QStringList availablePlans READ availablePlans NOTIFY availablePlansChanged)
    Q_PROPERTY(int currentPlanIndex READ currentPlanIndex WRITE setCurrentPlanIndex NOTIFY currentPlanIndexChanged)

public:
    explicit OptimizationModel(QObject *parent = nullptr);
    ~OptimizationModel();

    QStringList availablePlans() const;

    int currentPlanIndex() const { return currentIndex_; }
    void setCurrentPlanIndex(int index);

    void addPlan(AbstractOptimizationPlan *plan);
    AbstractOptimizationPlan *currentPlan() const;

    void optimize(const DrillNode* root, const DrillTransformModel *transformModel = nullptr);
    void generateOptimizedDrillDocument(DrillDocument &out) const;

signals:
    void availablePlansChanged();
    void currentPlanIndexChanged();
    void currentPanChanged();
    void optimized();

private:
    QVector<AbstractOptimizationPlan *> plans_;
    int currentIndex_;
};

#endif // OPTIMIZATIONMODEL_H
