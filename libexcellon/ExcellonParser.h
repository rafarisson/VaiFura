#ifndef EXCELLONPARSER_H
#define EXCELLONPARSER_H

#include "AbstractDrillParser.h"
#include "ExcellonLexer.h"

class ExcellonParser : public AbstractDrillParser
{
public:
    DrillModel parse(QTextStream &in) override;

private:
    ExcellonLexer lexer_;
};

#endif // EXCELLONPARSER_H
