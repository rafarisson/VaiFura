#ifndef DRILLHELPER_H
#define DRILLHELPER_H

#include <QPointF>
#include "DrillDocument.h"
#include "DrillDocumentModel.h"

class DrillHelper
{
public:
    template <typename F>
    static void forEachHole(const DrillDocumentModel *model,
                            const QPointF &delta,
                            F &&fn){
        if (!model || !model->document() || !model->document()->root())
            return;

        const DrillNode *root = model->document()->root();

        for (int t = 0; t < root->childCount(); ++t) {
            const DrillNode *toolNode = root->child(t);

            for (int h = 0; h < toolNode->childCount(); ++h) {
                const DrillNode *holeNode = toolNode->child(h);
                const Hole *hole = holeNode->hole();
                if (!hole)
                    continue;

                QPointF p(
                    hole->x + model->offset().x() + delta.x(),
                    hole->y + model->offset().y() + delta.y()
                    );

                double r = toolRadius(model, hole->toolId);

                fn(holeNode, hole, p, r);
            }
        }
    }

    static double toolRadius(const DrillDocumentModel *model, int toolId)
    {
        for (const auto &t : model->document()->tools())
            if (t.id == toolId)
                return t.mm * 0.5;
        return 0.2;
    }
};

#endif // DRILLHELPER_H
