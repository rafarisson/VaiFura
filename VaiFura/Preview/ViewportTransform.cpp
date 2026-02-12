#include "ViewportTransform.h"

QPointF ViewportTransform::toScreen(const QPointF &w) const
{
    return {
        size_.width() * 0.5 + (w.x() + pan_.x()) * zoom_,
        size_.height() * 0.5 - (w.y() + pan_.y()) * zoom_
    };
}

QPointF ViewportTransform::toWorld(const QPointF &s) const
{
    return {
        (s.x() - size_.width() * 0.5) / zoom_ - pan_.x(),
        -(s.y() - size_.height() * 0.5) / zoom_ - pan_.y()
    };
}

QRectF ViewportTransform::visibleWorldRect() const
{
    QPointF a = toWorld({0, 0});
    QPointF b = toWorld({size_.width(), size_.height()});
    return QRectF(a, b).normalized();
}

void ViewportTransform::fitWorldRect(const QRectF &r, double marginPx)
{
    if (r.isEmpty() || size_.isEmpty())
        return;

    double zoomX = (size_.width()  - 2.0 * marginPx) / r.width();
    double zoomY = (size_.height() - 2.0 * marginPx) / r.height();

    zoom_ = std::clamp(std::min(zoomX, zoomY), 0.1, 500.0);

    QPointF center = r.center();
    pan_ = QPointF(-center.x(), -center.y());
}
