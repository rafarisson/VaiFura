#include "DrillDocumentExportPreparer.h"
#include "DrillDocumentBuilder.h"
#include "DrillTransform.h"

void DrillDocumentExportPreparer::prepare(const DrillDocument &src, const DrillTransform &transform)
{
    DrillDocumentBuilder builder(&doc_);

    builder.clear();

    const DrillNode *root = src.root();

    for (int t = 0; t < root->childCount(); ++t) {
        const DrillNode *toolNode = root->child(t);

        if (!toolNode->isChecked())
            continue;

        const Tool *tool = toolNode->tool();
        builder.addTool(*tool);

        for (int h = 0; h < toolNode->childCount(); ++h) {
            const DrillNode *holeNode = toolNode->child(h);

            if (!holeNode->isChecked())
                continue;

            const Hole *hole = holeNode->hole();

            QPointF pos(hole->x, hole->y);
            pos = transform.apply(pos);

            builder.addHole({
                             pos.x(),
                             pos.y(),
                             hole->toolId
            });
        }
    }

    builder.build();
}
