#ifndef ABSTRACTDRILLPARSER_H
#define ABSTRACTDRILLPARSER_H

#include <QTextStream>
#include "DrillModel.h"

class AbstractDrillParser
{
public:
    virtual ~AbstractDrillParser() = default;
    virtual DrillModel parse(QTextStream &in) = 0;
};

#endif // ABSTRACTDRILLPARSER_H
