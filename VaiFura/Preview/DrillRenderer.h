#ifndef DRILLRENDERER_H
#define DRILLRENDERER_H

#include <QSGNode>

class DrillDocumentModel;
class DrillTransformModel;
class ViewportTransform;
class DrillNode;

class DrillRenderer
{
public:
    void build(QSGNode *root,
               const DrillDocumentModel *model,
               const DrillTransformModel *transform,
               const ViewportTransform &vp,
               const QColor &color,
               const QPointF &delta = {0, 0});

private:
    QSGGeometryNode *createCircleOutline(const QPointF &center,
                                         double radiusPx,
                                         double thicknessPx,
                                         const QColor &color,
                                         int segments = 32);
};

#endif // DRILLRENDERER_H
