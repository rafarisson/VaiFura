#include "NearestNeighborOptimization.h"
#include "DrillTransform.h"

void NearestNeighborOptimization::optimize(const DrillNode *root, const DrillTransform *transform)
{
    build(root);

    if (holes().isEmpty())
        return;

    const int n = holes().size();
    QVector<bool> visited(n, false);
    order_.reserve(n);

    int current = startIndexFromOrigin(transform);
    if (current == -1)
        return;

    order_.append(current);
    visited[current] = true;

    for (int i = 1; i < n; ++i) {
        int nextIndex = -1;
        double bestDist = std::numeric_limits<double>::max();

        for (int j = 0; j < n; ++j) {
            if (visited[j])
                continue;

            QPointF a = holes()[current].pos;
            QPointF b = holes()[j].pos;

            if (transform) {
                a = transform->apply(a);
                b = transform->apply(b);
            }

            double d = distance(a, b);
            if (d < bestDist) {
                bestDist = d;
                nextIndex = j;
            }
        }

        current = nextIndex;
        visited[current] = true;
        order_.append(current);
    }
}

int NearestNeighborOptimization::startIndexFromOrigin(const DrillTransform *transform) const
{
    const int n = holes().size();

    int closestIndex = -1;
    double bestDist = std::numeric_limits<double>::max();
    QPointF origin(0, 0);

    for (int i = 0; i < n; ++i) {
        QPointF p = holes()[i].pos;

        if (transform) {
            p = transform->apply(p);
        }

        double d = distance(origin, p);
        if (d < bestDist) {
            bestDist = d;
            closestIndex = i;
        }
    }

    return closestIndex;
}
