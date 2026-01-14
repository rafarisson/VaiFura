#ifndef EXCELLONDRILLPARSER_H
#define EXCELLONDRILLPARSER_H

#include "DrillParser.h"
#include "ExcellonLexer.h"

class ExcellonDrillParser : public DrillParser
{
public:
    bool parse(QTextStream &in, DrillDocumentBuilder &builder) override;

private:
    ExcellonLexer lexer_;
};

#endif // EXCELLONDRILLPARSER_H
