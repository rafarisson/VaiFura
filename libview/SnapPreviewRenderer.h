#ifndef SNAPPREVIEWRENDERER_H
#define SNAPPREVIEWRENDERER_H

#include <QColor>
#include "DrillRendererBase.h"

class SnapPreviewRenderer : public DrillRendererBase
{
protected:
    QColor holeColor(const DrillNode *holeNode) const override {
        return QColor(0, 255, 255, 120);
    }
};

#endif // SNAPPREVIEWRENDERER_H
