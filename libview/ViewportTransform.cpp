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

    double zx = (size_.width()  - marginPx * 2) / r.width();
    double zy = (size_.height() - marginPx * 2) / r.height();

    zoom_ = std::clamp(std::min(zx, zy), 1.0, 500.0);

    QPointF center = r.center();
    pan_ = -center;
}
