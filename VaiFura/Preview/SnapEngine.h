#ifndef SNAPENGINE_H
#define SNAPENGINE_H

#include <QPointF>

class SnapEngine
{
public:
    explicit SnapEngine() = default;

    void setGridStep(double s) { gridStep_ = s; }

    QPointF snap(const QPointF &world) const;

private:
    static double snap1(double v, double step);

    double gridStep_ = 1.0;
};

#endif // SNAPENGINE_H
