#include <QRegularExpression>
#include "ExcellonLexer.h"

ExcellonToken ExcellonLexer::lex(const QString &line) const
{
    const QString l = line.trimmed();

    if (l.isEmpty() || l.startsWith(';'))
        return {};

    if (l == "M48") return {ExcellonTokenType::HeaderStart};
    if (l == "%")   return {ExcellonTokenType::HeaderEnd};
    if (l == "M30") return {ExcellonTokenType::EndProgram};
    if (l == "M71") return {ExcellonTokenType::UnitsMetric};
    if (l == "M72") return {ExcellonTokenType::UnitsInch};
    if (l == "G90") return {ExcellonTokenType::G90};
    if (l == "G91") return {ExcellonTokenType::G91};

    if (l.startsWith('T')) {
        ExcellonToken t;
        t = lexToolDef(l);
        if (t.type != ExcellonTokenType::Unknown)
            return t;
        t = lexToolSelect(l);
        if (t.type != ExcellonTokenType::Unknown)
            return t;
    }

    if (l.contains('X') || l.contains('Y')) {
        ExcellonToken t = lexCoord(l);
        if (t.type != ExcellonTokenType::Unknown)
            return t;
    }

    return {};
}

ExcellonToken ExcellonLexer::lexToolDef(const QString &line) const
{
    static const QRegularExpression re(R"(^T(\d+)C([0-9.]+))");

    const auto m = re.match(line);
    if (!m.hasMatch())
        return {};

    ExcellonToken t;
    t.type  = ExcellonTokenType::ToolDef;
    t.tool  = m.captured(1).toInt();
    t.value = m.captured(2).toDouble();
    return t;
}

ExcellonToken ExcellonLexer::lexToolSelect(const QString &line) const
{
    static const QRegularExpression re(R"(^T(\d+)$)");

    const auto m = re.match(line);
    if (!m.hasMatch())
        return {};

    ExcellonToken t;
    t.type = ExcellonTokenType::ToolSelect;
    t.tool = m.captured(1).toInt();
    return t;
}

ExcellonToken ExcellonLexer::lexCoord(const QString &line) const
{
    static const QRegularExpression re(R"(X(-?\d+)|Y(-?\d+))");

    ExcellonToken t;
    t.type = ExcellonTokenType::Coord;

    auto it = re.globalMatch(line);
    while (it.hasNext()) {
        const auto m = it.next();

        if (m.captured(1).length()) {
            t.hasX = true;
            t.x = m.captured(1).toDouble();
        }

        if (m.captured(2).length()) {
            t.hasY = true;
            t.y = m.captured(2).toDouble();
        }
    }

    if (!t.hasX && !t.hasY)
        return {};

    return t;
}
