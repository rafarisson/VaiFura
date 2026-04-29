#include "NoneOptimization.h"

void NoneOptimization::optimize(const DrillNode *root, const DrillTransform *transform)
{
    build(root);

    order_.clear();
    order_.reserve(holes().size());

    for (int i = 0; i < holes().size(); ++i)
        order_.append(i);
}
