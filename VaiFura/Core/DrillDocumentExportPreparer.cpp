#include "DrillDocumentExportPreparer.h"
#include "DrillDocumentBuilder.h"

void DrillDocumentExportPreparer::prepare(const DrillDocument &src, const QPointF &offset)
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

            Hole shifted = *hole;
            shifted.x += offset.x();
            shifted.y += offset.y();

            builder.addHole(shifted);
        }
    }

    builder.build();
}
