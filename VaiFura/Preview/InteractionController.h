#ifndef INTERACTIONCONTROLLER_H
#define INTERACTIONCONTROLLER_H

#include <QPointF>

class ViewportTransform;
class SnapEngine;
class DrillTransformModel;

class InteractionController
{
public:
    explicit InteractionController() = default;

    void setViewport(ViewportTransform *v) { viewport_ = v; }
    void setSnap(SnapEngine *s) { snap_ = s; }
    void setTransformModel(DrillTransformModel *m) { transformModel_ = m; }

    void mousePress(const QPointF &pos, Qt::MouseButton button);
    void mouseMove(const QPointF &pos);
    void mouseRelease(const QPointF &pos, Qt::MouseButton button);
    void wheel(double delta);

    bool snapActive() const { return snapActive_; }
    void initSnap();
    QPointF snapDelta() const;

private:
    ViewportTransform *viewport_ = nullptr;
    SnapEngine *snap_ = nullptr;
    DrillTransformModel *transformModel_ = nullptr;

    bool panning_ = false;
    bool movingDrills_ = false;

    QPointF lastPos_;
    QPointF moveStartWorld_;
    QPointF moveStartOffset_;

    QPointF snapPreviewWorld_;
    bool snapActive_ = false;
};

#endif // INTERACTIONCONTROLLER_H
