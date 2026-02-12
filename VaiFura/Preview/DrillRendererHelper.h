#ifndef DRILLRENDERERHELPER_H
#define DRILLRENDERERHELPER_H

#include <QPointF>
#include "DrillDocument.h"
#include "DrillDocumentModel.h"
#include "DrillTransformModel.h"
#include "DrillHelper.h"

class DrillRendererHelper
{
public:
    template <typename F>
    static void forEachHole(const DrillDocumentModel *model, const DrillTransformModel *transform, const QPointF &delta, F &&fn) {
        if (!model || !model->document())
            return;

        double tool_mm = 0;

        DrillHelper::forEachHole(
            model->document()->root(),
            [&](const DrillNode *toolNode) {
                if (toolNode && toolNode->tool())
                    tool_mm = toolNode->tool()->mm;
            },
            [&](const DrillNode *holeNode, const QPointF &pos) {
                QPointF o = transform ? transform->offset() : QPointF();
                const Hole *hole = holeNode->hole();
                QPointF p(pos.x() + o.x() + delta.x(),
                          pos.y() + o.y() + delta.y());
                // double r = toolRadius(model, hole->toolId);
                double r = toolRadius(tool_mm);
                fn(holeNode, hole, p, r);
            });
    }

    static double toolRadius(double mm) {
        return mm * 0.5;
    }

    static double toolRadius(const DrillDocumentModel *model, int toolId)
    {
        for (const auto &t : model->document()->tools())
            if (t.id == toolId)
                return toolRadius(t.mm);
        return 0.2;
    }
};

#endif // DRILLRENDERERHELPER_H
