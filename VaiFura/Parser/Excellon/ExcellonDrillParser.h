#ifndef EXCELLONDRILLPARSER_H
#define EXCELLONDRILLPARSER_H

#include <QPointF>
#include "Units.h"
#include "DrillParser.h"
#include "ExcellonLexer.h"

class ExcellonDrillParser : public DrillParser
{
public:
    bool parse(QTextStream &in, DrillDocumentBuilder &builder) override;

private:
    void reset();
    void addHole(const ExcellonToken &token, DrillDocumentBuilder &builder);
    double normalizeCoord(double value) const;

private:
    ExcellonLexer lexer_;
    int tool_;
    Units unit_;
    bool absolute_;

    double coordScale_;
    double lastX_;
    double lastY_;
};

#endif // EXCELLONDRILLPARSER_H
