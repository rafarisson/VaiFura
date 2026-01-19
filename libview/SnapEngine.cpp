#include "SnapEngine.h"

QPointF SnapEngine::snap(const QPointF &w) const
{
    return { snap1(w.x(), gridStep_), snap1(w.y(), gridStep_) };
}

double SnapEngine::snap1(double v, double step)
{
    return std::round(v / step) * step;
}
