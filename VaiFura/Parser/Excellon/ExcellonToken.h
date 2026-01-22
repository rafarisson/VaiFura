#ifndef EXCELLONTOKEN_H
#define EXCELLONTOKEN_H

enum class ExcellonTokenType {
    HeaderStart,
    HeaderEnd,
    ToolDef,
    ToolSelect,
    Coord,
    G90,
    G91,
    Unknown
};

struct ExcellonToken
{
    ExcellonTokenType type;
    int tool = -1;
    double x = 0;
    double y = 0;
    double value = 0;
};

#endif // EXCELLONTOKEN_H
