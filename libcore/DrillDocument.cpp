#include "DrillDocument.h"

DrillDocument::DrillDocument(const QVector<Tool> &t, const QVector<Hole> &h)
{
    tools_ = t;
    holes_ = h;
}

void DrillDocument::clear()
{
    tools_.clear();
    holes_.clear();
}
