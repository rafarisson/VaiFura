#ifndef NEARESTNEIGHBOROPTIMIZATION_H
#define NEARESTNEIGHBOROPTIMIZATION_H

#include "AbstractOptimizationPlan.h"

class NearestNeighborOptimization : public AbstractOptimizationPlan
{
public:
    void optimize(const DrillNode* root) override;
};

#endif // NEARESTNEIGHBOROPTIMIZATION_H
