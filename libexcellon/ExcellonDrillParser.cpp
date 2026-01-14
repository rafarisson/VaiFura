#include "ExcellonDrillParser.h"
#include "DrillDocumentBuilder.h"

bool ExcellonDrillParser::parse(QTextStream &in, DrillDocumentBuilder &builder)
{
    int currentTool = -1;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith(';'))
            continue;

        auto token = lexer_.lex(line);

        switch (token.type) {
        case ExcellonTokenType::ToolDef:
            builder.addTool({token.tool, token.value});
            break;
        case ExcellonTokenType::ToolSelect:
            currentTool = token.tool;
            break;
        case ExcellonTokenType::Coord:
            if (currentTool >= 0)
                builder.addHole({token.x, token.y, currentTool});
            break;
        default:
            break;
        }
    }

    return true;
}
