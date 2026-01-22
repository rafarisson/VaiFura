#include <QRegularExpression>
#include "ExcellonLexer.h"

ExcellonToken ExcellonLexer::lex(const QString &line) const
{
    if (line.isEmpty())
        return {ExcellonTokenType::Unknown};

    if (line == "M48")
        return {ExcellonTokenType::HeaderStart};
    if (line == "%")
        return {ExcellonTokenType::HeaderEnd};
    if (line == "G90")
        return {ExcellonTokenType::G90};
    if (line == "G91")
        return {ExcellonTokenType::G91};

    static QRegularExpression toolDef("^T(\\d+)C([0-9.]+)");
    auto m = toolDef.match(line);
    if (m.hasMatch())
        return {ExcellonTokenType::ToolDef,
                m.captured(1).toInt(),
                0, 0,
                m.captured(2).toDouble()};

    static QRegularExpression toolSel("^T(\\d+)$");
    m = toolSel.match(line);
    if (m.hasMatch())
        return {ExcellonTokenType::ToolSelect, m.captured(1).toInt()};

    static QRegularExpression coord("^X(-?\\d+)Y(-?\\d+)");
    m = coord.match(line);
    if (m.hasMatch())
        return {ExcellonTokenType::Coord,
                -1,
                m.captured(1).toDouble() / 1000.0,
                m.captured(2).toDouble() / 1000.0};

    return {ExcellonTokenType::Unknown};
}
