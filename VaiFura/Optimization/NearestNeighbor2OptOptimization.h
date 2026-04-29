#ifndef NEARESTNEIGHBOR2OPTOPTIMIZATION_H
#define NEARESTNEIGHBOR2OPTOPTIMIZATION_H

#include "NearestNeighborOptimization.h"

class NearestNeighbor2OptOptimization : public NearestNeighborOptimization
{
public:
    QString name() const override { return "Nearest Neighbor + 2-opt"; }
    void optimize(const DrillNode *root, const DrillTransform *transform) override;
private:
    void twoOptImprove(const DrillTransform *transform);
};

#endif // NEARESTNEIGHBOR2OPTOPTIMIZATION_H
