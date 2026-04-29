#include <QHash>
#include "AbstractOptimizationPlan.h"
#include "DrillHelper.h"

double AbstractOptimizationPlan::distance(const QPointF &a, const QPointF &b) const
{
    double dx = a.x() - b.x();
    double dy = a.y() - b.y();
    return std::sqrt(dx * dx + dy * dy);
}

void AbstractOptimizationPlan::build(const DrillNode *root)
{
    holes_.clear();
    order_.clear();

    if (!root)
        return;

    DrillHelper::forEachHole(
        root,
        [&](const DrillNode *toolNode) {

        },
        [&](const DrillNode *holeNode, const QPointF &pos) {
            if (!holeNode->isChecked())
                return;
            holes_.append({
                holeNode,
                pos,
            });
        });
}
