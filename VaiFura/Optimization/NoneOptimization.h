#ifndef NONEOPTIMIZATION_H
#define NONEOPTIMIZATION_H

#include "AbstractOptimizationPlan.h"

class NoneOptimization : public AbstractOptimizationPlan
{
public:
    QString name() const override { return "None"; }
    void optimize(const DrillNode *root, const DrillTransform *transform) override;
private:
};

#endif // NONEOPTIMIZATION_H
