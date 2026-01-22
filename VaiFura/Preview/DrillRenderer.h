#ifndef DRILLRENDERER_H
#define DRILLRENDERER_H

#include "DrillRendererBase.h"

class DrillRenderer : public DrillRendererBase
{
protected:
    QColor holeColor(const DrillNode *holeNode) const override;
};

#endif // DRILLRENDERER_H
