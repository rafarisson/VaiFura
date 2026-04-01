#include "DrillTransform.h"

QPointF DrillTransform::apply(const QPointF &p) const
{
    return toTransform().map(p);
}

QPointF DrillTransform::applyInverse(const QPointF &p) const
{
    return toTransform().inverted().map(p);
}

void DrillTransform::clear()
{
    offset = {0, 0};
    rotation = 0;
    mirrorX = false;
    mirrorY = false;
}

QTransform DrillTransform::toTransform() const
{
    QTransform t;
    t.translate(origin.x(), origin.y());
    t.translate(offset.x(), offset.y());
    t.translate(pivot.x(), pivot.y());
    t.rotate(rotation);
    t.scale(mirrorX ? -1 : 1, mirrorY ? -1 : 1);
    t.translate(-pivot.x(), -pivot.y());
    t.translate(-origin.x(), -origin.y());
    return t;
}
