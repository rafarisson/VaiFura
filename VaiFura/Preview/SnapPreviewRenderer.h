#ifndef SNAPPREVIEWRENDERER_H
#define SNAPPREVIEWRENDERER_H

#include <QColor>
#include "DrillRendererBase.h"

class SnapPreviewRenderer : public DrillRendererBase
{
protected:
    QColor holeColor(const DrillNode *holeNode) const override {
        QColor c = DrillRendererBase::holeColor(holeNode);
        c.setAlpha(120);
        return c;
    }
};

#endif // SNAPPREVIEWRENDERER_H
