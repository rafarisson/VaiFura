#include "NearestNeighborOptimization.h"
#include <qdebug.h>

void NearestNeighborOptimization::optimize(const DrillNode *root)
{
    build(root);

    if (holes().isEmpty())
        return;

    const int n = holes().size();
    QVector<bool> visited(n, false);
    order_.reserve(n);

    int current = 0;
    order_.append(current);
    visited[current] = true;

    for (int i = 1; i < n; ++i) {
        int nextIndex = -1;
        double bestDist = std::numeric_limits<double>::max();

        for (int j = 0; j < n; ++j) {
            if (visited[j])
                continue;

            double d = distance(holes()[current].pos, holes()[j].pos);
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
