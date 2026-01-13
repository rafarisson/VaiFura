#ifndef DRILLMODEL_H
#define DRILLMODEL_H

#include "VaiFuraTypes.h"

class DrillModel
{
public:
    const QVector<Tool>& tools() const { return tools_; }
    const QVector<Drill>& drills() const { return drills_; }

    void clear() {
        tools_.clear();
        drills_.clear();
    }

private:
    friend class DrillBuilder;
    QVector<Tool> tools_;
    QVector<Drill> drills_;
};

#endif // DRILLMODEL_H
