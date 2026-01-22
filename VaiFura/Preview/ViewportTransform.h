#ifndef VIEWPORTTRANSFORM_H
#define VIEWPORTTRANSFORM_H

#include <QPointF>
#include <QSizeF>
#include <QRectF>

class ViewportTransform
{
public:
    explicit ViewportTransform() = default;

    void setViewportSize(const QSizeF &s) { size_ = s; }
    void setZoom(double z) { zoom_ = z; }
    void setPan(const QPointF &p) { pan_ = p; }

    double zoom() const { return zoom_; }
    QPointF pan() const { return pan_; }

    QPointF toScreen(const QPointF &w) const;
    QPointF toWorld(const QPointF &s) const;

    QRectF visibleWorldRect() const;

    void fitWorldRect(const QRectF &r, double marginPx);

private:
    QSizeF size_;
    double zoom_ = 20.0;
    QPointF pan_{0, 0};
};

#endif // VIEWPORTTRANSFORM_H
