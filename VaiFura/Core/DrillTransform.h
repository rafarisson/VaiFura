#ifndef DRILLTRANSFORM_H
#define DRILLTRANSFORM_H

#include <QPointF>

class DrillTransform
{
public:
    QPointF apply(const QPointF &p) const;
    // QPointF applyInverse(const QPointF &p) const;
    void clear();

    QPointF pivot = {0, 0};
    QPointF offset = {0, 0};
    double rotation = 0.0;
    bool mirrorX = false;
    bool mirrorY = false;
};

#endif // DRILLTRANSFORM_H
