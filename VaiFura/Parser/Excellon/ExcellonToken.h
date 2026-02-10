#ifndef EXCELLONTOKEN_H
#define EXCELLONTOKEN_H

enum class ExcellonTokenType
{
    HeaderStart,
    HeaderEnd,
    ToolDef,
    ToolSelect,
    Coord,
    UnitsMetric,
    UnitsInch,
    G90,
    G91,
    EndProgram,
    Unknown
};

struct ExcellonToken
{
    ExcellonTokenType type = ExcellonTokenType::Unknown;
    int tool = -1;
    bool hasX = false;
    bool hasY = false;
    double x = 0;
    double y = 0;
    double value = 0;
};

#endif // EXCELLONTOKEN_H
