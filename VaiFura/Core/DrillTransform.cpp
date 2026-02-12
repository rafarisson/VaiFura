#include <QtMath>
#include "DrillTransform.h"

QPointF DrillTransform::apply(const QPointF &p) const
{
    QPointF r = p;

    if (mirrorX)
        r.setX(-r.x());
    if (mirrorY) r.setY(-r.y());

    if (!qFuzzyIsNull(rotation)) {
        double a = qDegreesToRadians(rotation);
        double cs = std::cos(a);
        double sn = std::sin(a);
        r = {
            r.x() * cs - r.y() * sn,
            r.x() * sn + r.y() * cs
        };
    }

    r += offset;
    return r;
}

// QPointF DrillTransform::applyInverse(const QPointF &p) const
// {
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
// }

void DrillTransform::clear()
{
    offset = {0, 0};
    rotation = 0;
    mirrorX = false;
    mirrorY = false;
}
