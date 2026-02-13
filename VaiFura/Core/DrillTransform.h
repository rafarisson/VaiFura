#ifndef DRILLTRANSFORM_H
#define DRILLTRANSFORM_H

#include <QPointF>
#include <QTransform>

class DrillTransform
{
public:
    QPointF apply(const QPointF &p) const;
    QPointF applyInverse(const QPointF &p) const;
    void clear();

    QPointF origin = {0, 0};
    QPointF pivot = {0, 0};
    QPointF offset = {0, 0};
    double rotation = 0.0;
    bool mirrorX = false;
    bool mirrorY = false;

private:
    QTransform toTransform() const;
};

#endif // DRILLTRANSFORM_H
