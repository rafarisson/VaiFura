#include <QColor>
#include "DrillRenderer.h"
#include "DrillDocumentModel.h"
#include "DrillNode.h"

QColor DrillRenderer::holeColor(const DrillNode *holeNode) const
{
    return holeNode->isChecked() ? Qt::cyan : Qt::darkGray;
}
