#ifndef DRILLHELPER_H
#define DRILLHELPER_H

#include <QPointF>
#include "DrillDocument.h"

class DrillHelper
{
public:
    template <typename OnTool, typename OnHole>
    static void forEachHole(const DrillNode *root, OnTool &&onTool, OnHole &&onHole) {
        if (!root)
            return;

        for (int t = 0; t < root->childCount(); ++t) {
            const DrillNode *toolNode = root->child(t);
            const Tool *tool = toolNode->tool();
            if (!tool)
                continue;

            onTool(toolNode);

            for (int h = 0; h < toolNode->childCount(); ++h) {
                const DrillNode *holeNode = toolNode->child(h);
                const Hole *hole = holeNode->hole();
                if (!hole)
                    continue;

                onHole(holeNode, QPointF(hole->x, hole->y));
            }
        }
    }
};

#endif // DRILLHELPER_H
