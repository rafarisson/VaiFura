#include "ExcellonDrillParser.h"
#include "DrillDocumentBuilder.h"

bool ExcellonDrillParser::parse(QTextStream &in, DrillDocumentBuilder &builder)
{
    reset();

    while (!in.atEnd()) {
        const QString line = in.readLine();
        const ExcellonToken token = lexer_.lex(line);

        if (token.type == ExcellonTokenType::EndProgram)
            break;

        switch (token.type) {
        case ExcellonTokenType::UnitsMetric:
            unit_ = DrillUnits::MM;
            break;
        case ExcellonTokenType::UnitsInch:
            unit_ = DrillUnits::INCH;
            break;
        case ExcellonTokenType::G90:
            absolute_ = true;
            break;
        case ExcellonTokenType::G91:
            absolute_ = false;
            break;
        case ExcellonTokenType::ToolDef:
            builder.addTool({token.tool, token.value});
            break;
        case ExcellonTokenType::ToolSelect:
            tool_ = token.tool;
            break;
        case ExcellonTokenType::Coord:
            addHole(token, builder);
            break;
        default:
            break;
        }
    }

    return true;
}

void ExcellonDrillParser::reset()
{
    tool_ = -1;
    unit_ = DrillUnits::MM;
    absolute_ = true;

    coordScale_ = 1000.0;
    lastX_ = 0.0;
    lastY_ = 0.0;
}

void ExcellonDrillParser::addHole(const ExcellonToken &token, DrillDocumentBuilder &builder)
{
    if (tool_ < 0)
        return;

    double x = lastX_;
    double y = lastY_;

    if (token.hasX) {
        double v = normalizeCoord(token.x);
        x = absolute_ ? v : lastX_ + v;
    }

    if (token.hasY) {
        double v = normalizeCoord(token.y);
        y = absolute_ ? v : lastY_ + v;
    }

    lastX_ = x;
    lastY_ = y;

    builder.addHole({x, y, tool_});
}

double ExcellonDrillParser::normalizeCoord(double value) const
{
    double v = value / coordScale_;

    if (unit_ == DrillUnits::INCH)
        v *= 25.4;

    return v;
}
