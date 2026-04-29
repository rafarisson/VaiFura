#ifndef OPTIMIZATIONRENDERER_H
#define OPTIMIZATIONRENDERER_H

#include <QSGNode>
#include <QSGSimpleTextureNode>

class OptimizationModel;
class DrillTransformModel;
class ViewportTransform;
class QQuickWindow;

class OptimizationRenderer
{
public:
    bool showPath() const { return showPath_; }
    void setShowPath(bool enabled);

    bool showOrder() const { return showOrder_; }
    void setShowOrder(bool enabled);

    void build(QSGNode *root,
               const OptimizationModel *model,
               const DrillTransformModel *transform,
               const ViewportTransform &vp,
               const QColor &color,
               QQuickWindow *window);

private:
    QSGGeometryNode* createLine(const QPointF &a,
                                const QPointF &b,
                                const QColor &color,
                                float thickness);

    QSGSimpleTextureNode* createText(const QPointF &pos,
                                     const QString &text,
                                     const QColor &color,
                                     QQuickWindow *window);

    bool showPath_ = false;
    bool showOrder_ = false;
};

#endif // OPTIMIZATIONRENDERER_H
