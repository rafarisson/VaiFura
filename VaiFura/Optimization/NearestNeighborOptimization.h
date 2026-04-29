#ifndef NEARESTNEIGHBOROPTIMIZATION_H
#define NEARESTNEIGHBOROPTIMIZATION_H

#include "AbstractOptimizationPlan.h"

class NearestNeighborOptimization : public AbstractOptimizationPlan
{
public:
    QString name() const override { return "Nearest Neighbor"; }
    void optimize(const DrillNode *root, const DrillTransform *transform) override;
private:
    int startIndexFromOrigin(const DrillTransform *transform) const;
};

#endif // NEARESTNEIGHBOROPTIMIZATION_H
