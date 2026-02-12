#include "InteractionController.h"
#include "SnapEngine.h"
#include "ViewportTransform.h"
#include "DrillTransformModel.h"

QPointF InteractionController::snapDelta() const
{
    if (!transformModel_)
        return {0, 0};

    return snapPreviewWorld_ - transformModel_->offset();
}

void InteractionController::mousePress(const QPointF &pos, Qt::MouseButton button)
{
    lastPos_ = pos;

    if (button == Qt::LeftButton) {
        panning_ = true;
        return;
    }

    if (button == Qt::RightButton && transformModel_ && viewport_) {
        movingDrills_ = true;
        moveStartWorld_ = viewport_->toWorld(pos);
        moveStartOffset_ = transformModel_->offset();
        snapActive_ = true;
    }
}

void InteractionController::mouseMove(const QPointF &pos)
{
    if (panning_ && viewport_) {
        QPointF deltaPx = pos - lastPos_;
        lastPos_ = pos;

        QPointF pan = viewport_->pan();
        pan.rx() += deltaPx.x() / viewport_->zoom();
        pan.ry() -= deltaPx.y() / viewport_->zoom();
        viewport_->setPan(pan);

        return;
    }

    if (movingDrills_ && transformModel_ && viewport_) {
        QPointF currentWorld = viewport_->toWorld(pos);
        QPointF deltaWorld = currentWorld - moveStartWorld_;
        QPointF candidate = moveStartOffset_ + deltaWorld;

        if (snap_)
            snapPreviewWorld_ = snap_->snap(candidate);
        else
            snapPreviewWorld_ = candidate;

        snapActive_ = true;
    }
}

void InteractionController::mouseRelease(const QPointF &, Qt::MouseButton button)
{
    if (button == Qt::LeftButton) {
        panning_ = false;
    }

    if (button == Qt::RightButton && transformModel_) {
        movingDrills_ = false;

        if (snapActive_) {
            transformModel_->setOffset(snapPreviewWorld_);
            snapActive_ = false;
        }
    }
}

void InteractionController::wheel(double delta)
{
    if (!viewport_)
        return;

    double z = viewport_->zoom();
    viewport_->setZoom(z * (delta > 0 ? 1.1 : 0.9));
}
