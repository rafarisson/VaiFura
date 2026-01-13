#ifndef EXCELLONMODEL_H
#define EXCELLONMODEL_H

#include "ExcellonTypes.h"

class ExcellonVisitor;

class DrillModel
{
public:
    const QVector<Tool>& tools() const { return tools_; }
    const QVector<Drill>& drills() const { return drills_; }

private:
    friend class ExcellonParser;

    QVector<Tool> tools_;
    QVector<Drill> drills_;
};

#endif // EXCELLONMODEL_H
