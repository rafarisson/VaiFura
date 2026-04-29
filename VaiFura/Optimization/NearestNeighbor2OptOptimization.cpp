#include "NearestNeighbor2OptOptimization.h"
#include "DrillTransform.h"

void NearestNeighbor2OptOptimization::optimize(const DrillNode *root, const DrillTransform *transform)
{
    NearestNeighborOptimization::optimize(root, transform);
    twoOptImprove(transform);
}

void NearestNeighbor2OptOptimization::twoOptImprove(const DrillTransform *transform)
{
    const int n = order_.size();
    if (n < 4)
        return;

    QVector<QPointF> pts(n);
    for (int i = 0; i < n; ++i) {
        QPointF p = holes()[order_[i]].pos;
        pts[i] = transform ? transform->apply(p) : p;
    }

    bool improved = true;
    int maxIterations = 5;
    int iter = 0;

    while (improved && iter++ < maxIterations) {
        improved = false;

        for (int i = 0; i < n - 2; ++i) {
            for (int k = i + 2; k < n - 1; ++k) {

                const QPointF &a = pts[i];
                const QPointF &b = pts[i + 1];
                const QPointF &c = pts[k];
                const QPointF &d = pts[k + 1];

                double currentDist = distance(a, b) + distance(c, d);
                double newDist     = distance(a, c) + distance(b, d);

                if (newDist < currentDist) {
                    std::reverse(order_.begin() + i + 1, order_.begin() + k + 1);
                    std::reverse(pts.begin() + i + 1, pts.begin() + k + 1);
                    improved = true;
                }
            }
        }
    }
}
