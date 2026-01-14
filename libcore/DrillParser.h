#ifndef DRILLPARSER_H
#define DRILLPARSER_H

#include <QTextStream>

class DrillDocumentBuilder;

class DrillParser
{
public:
    virtual ~DrillParser() = default;
    virtual bool parse(QTextStream &in, DrillDocumentBuilder &builder) = 0;
};

#endif // DRILLPARSER_H
