#ifndef OPTIMIZATIONRENDERER_H
#define OPTIMIZATIONRENDERER_H

#include <QSGNode>

class OptimizationModel;
class DrillTransformModel;
class ViewportTransform;

class OptimizationRenderer
{
public:
    void build(QSGNode *root,
               const OptimizationModel *model,
               const DrillTransformModel *transform,
               const ViewportTransform &vp,
               const QColor &color);

private:
    QSGGeometryNode* createLine(const QPointF &a,
                                const QPointF &b,
                                const QColor &color,
                                float thickness);
};

#endif // OPTIMIZATIONRENDERER_H
