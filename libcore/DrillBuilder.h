#ifndef DRILLBUILDER_H
#define DRILLBUILDER_H

#include "DrillModel.h"

class DrillBuilder
{
public:
    DrillBuilder &addTool(const Tool &tool)
    {
        model_.tools_.append(tool);
        return *this;
    }

    DrillBuilder &addDrill(const Drill &drill)
    {
        model_.drills_.append(drill);
        return *this;
    }

    DrillModel build()
    {
        return std::move(model_);
    }

private:
    DrillModel model_;
};

#endif // DRILLBUILDER_H
