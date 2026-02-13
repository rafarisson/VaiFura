#include "DrillTransform.h"

QPointF DrillTransform::apply(const QPointF &p) const
{
    return toTransform().map(p);

    // QPointF r = p - pivot;

    // if (mirrorX)
    //     r.setX(-r.x());
    // if (mirrorY)
    //     r.setY(-r.y());

    // if (!qFuzzyIsNull(rotation)) {
    //     double a = qDegreesToRadians(rotation);
    //     double cs = std::cos(a);
    //     double sn = std::sin(a);
    //     r = {
    //         r.x() * cs - r.y() * sn,
    //         r.x() * sn + r.y() * cs
    //     };
    // }

    // r += pivot;
    // r += offset;

    // return r;
}

QPointF DrillTransform::applyInverse(const QPointF &p) const
{
    return toTransform().inverted().map(p);

//     QPointF r = p - offset;

//     if (!qFuzzyIsNull(rotation)) {
//         double a = qDegreesToRadians(-rotation);
//         double cs = std::cos(a);
//         double sn = std::sin(a);
//         r = {
//             r.x() * cs - r.y() * sn,
//             r.x() * sn + r.y() * cs
//         };
//     }

//     if (mirrorX)
//         r.setX(-r.x());
//     if (mirrorY)
//         r.setY(-r.y());

//     return r;
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
    t.translate(-origin.x(), -origin.y());
    t.translate(pivot.x(), pivot.y());
    t.rotate(rotation);
    t.scale(mirrorX ? -1 : 1, mirrorY ? -1 : 1);
    t.translate(-pivot.x(), -pivot.y());
    t.translate(origin.x(), origin.y());
    t.translate(offset.x(), offset.y());
    return t;
}
