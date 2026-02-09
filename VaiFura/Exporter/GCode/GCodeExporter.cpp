#include <QDir>
#include <QFileInfo>
#include "GCodeExporter.h"
#include "DrillDocument.h"
#include "DrillHelper.h"
#include "SettingsReader.h"

QString GCodeExporter::settingsFile() const
{
    return "gcodeexporter.json";
}

QVector<Settings> GCodeExporter::defaultSettings() const
{
    return {
        // Settings{
        //     GCodeKeys::Z_TOOL_CHANGE,
        //     "Tool Change Height",
        //     "Safe Z height used for tool change. This is the home or predefined safe position and is not part of the drilling cycle.",
        //     "mm",
        //     GCodeDefault::Z_TOOL_CHANGE,
        //     Settings::Number
        // },
        Settings{
            GCodeKeys::Z_MOVE,
            "Move Height",
            "Z height used for rapid movements between holes. The tool always returns to this height before moving in X/Y.",
            "mm",
            GCodeDefault::Z_MOVE,
            Settings::Number
        },
        Settings{
            GCodeKeys::XY_MOVE_FEED,
            "Move Feed Rate",
            "Feed rate used for X/Y movements while the tool is at the move height (Z_MOVE).",
            "mm/min",
            GCodeDefault::XY_MOVE_FEED,
            Settings::Number
        },
        Settings{
            GCodeKeys::Z_DRILL_OFFSET,
            "Drill Offset",
            "Relative Z offset applied from the move height to perform drilling. This value should be negative to define the drilling depth.",
            "mm",
            GCodeDefault::Z_DRILL_OFFSET,
            Settings::Number
        },
        Settings{
            GCodeKeys::Z_DRILL_FEED,
            "Drill Feed Rate",
            "Feed rate used when moving down from the move height to the drilling depth.",
            "mm/min",
            GCodeDefault::Z_DRILL_FEED,
            Settings::Number
        },
        Settings{
            GCodeKeys::Z_RETRACT_FEED,
            "Retract Feed Rate",
            "Feed rate used when retracting the tool from the drilling depth back to the move height.",
            "mm/min",
            GCodeDefault::Z_RETRACT_FEED,
            Settings::Number
        },
        Settings{
            GCodeKeys::FILE_PER_TOOL,
            "Generate File Per Tool",
            "When enabled, a separate output file is generated for each tool instead of combining all tools into a single file.",
            "",
            GCodeDefault::FILE_PER_TOOL,
            Settings::Boolean
        }
    };
}

bool GCodeExporter::save(const QString &fileName, const DrillDocument &document, const QVector<Settings> &settings)
{
    if (fileName.isEmpty() || document.holes().empty() || !document.root()->childCount())
        return false;

    settings_ = GCodeSettings::from(settings);
    decodeFileName(fileName);

    if (!settings_.filePerTool)
        open();

    DrillHelper::forEachHole(
        document.root(),
        [&](const DrillNode *toolNode) {
            exportTool(toolNode);
        },
        [&](const DrillNode *holeNode, const QPointF &pos) {
            exportHole(holeNode, pos);
        });

    close();

    return true;
}

void GCodeExporter::decodeFileName(const QString &fileName)
{
    QFileInfo finfo(fileName);
    basePath_ = finfo.path();
    baseName_ = finfo.baseName();
}

void GCodeExporter::open(const QString &fileName)
{
    QString fn = QDir(basePath_).filePath(baseName_);
    if (!fileName.isEmpty())
        fn += fileName;

    file_.setFileName(fn + ".gcode");

    if (!file_.open(QIODevice::WriteOnly))
        return;

    out_.setDevice(&file_);
}

void GCodeExporter::close()
{
    if (file_.isOpen())
        file_.close();
}

void GCodeExporter::exportTool(const DrillNode *toolNode)
{
    if (settings_.filePerTool) {
        close();
        open(QString("_tool_%1").arg(toolNode->tool()->mm));
    }

    out_ << "; Tool " << toolNode->tool()->mm << "\n";
}

void GCodeExporter::exportHole(const DrillNode *holeNode, const QPointF &pos)
{
    if (!file_.isOpen())
        return;

    out_ << "; Hole " << "\n";
    out_ << "G0 X" << pos.x() << " Y" << pos.y() << " F" << settings_.xyMoveFeed << "\n";
    out_ << "G1 Z" << settings_.zDrillOffset << " F" << settings_.zDrillFeed << "\n";
    out_ << "G0 Z" << settings_.zMove << " F" << settings_.zRetractFeed << "\n";
}

GCodeExporter::GCodeSettings GCodeExporter::GCodeSettings::from(const QVector<Settings> &settings)
{
    SettingsReader setts(settings);
    return {
        // setts.number(GCodeKeys::Z_TOOL_CHANGE,  GCodeDefault::Z_TOOL_CHANGE),
        setts.number(GCodeKeys::Z_MOVE,         GCodeDefault::Z_MOVE),
        setts.number(GCodeKeys::XY_MOVE_FEED,   GCodeDefault::XY_MOVE_FEED),
        setts.number(GCodeKeys::Z_DRILL_OFFSET, GCodeDefault::Z_DRILL_OFFSET),
        setts.number(GCodeKeys::Z_DRILL_FEED,   GCodeDefault::Z_DRILL_FEED),
        setts.number(GCodeKeys::Z_RETRACT_FEED, GCodeDefault::Z_RETRACT_FEED),
        setts.boolean(GCodeKeys::FILE_PER_TOOL, GCodeDefault::FILE_PER_TOOL)
    };
}

