#ifndef GCODEEXPORTER_H
#define GCODEEXPORTER_H

#include <QFile>
#include <QTextStream>
#include "AbstractExporter.h"

class DrillNode;

namespace GCodeKeys {
// inline static constexpr auto Z_TOOL_CHANGE  = "Z_TOOL_CHANGE";
inline static constexpr auto Z_MOVE         = "Z_MOVE";
inline static constexpr auto XY_MOVE_FEED   = "XY_MOVE_FEED";
inline static constexpr auto Z_DRILL_OFFSET = "Z_DRILL_OFFSET";
inline static constexpr auto Z_DRILL_FEED   = "Z_DRILL_FEED";
inline static constexpr auto Z_RETRACT_FEED = "Z_RETRACT_FEED";
inline static constexpr auto FILE_PER_TOOL  = "FILE_PER_TOOL";
}

namespace GCodeDefault {
// inline static constexpr double Z_TOOL_CHANGE    = 20.0;
inline static constexpr double Z_MOVE           = 5.0;
inline static constexpr double XY_MOVE_FEED     = 3000.0;
inline static constexpr double Z_DRILL_OFFSET   = -2.0;
inline static constexpr double Z_DRILL_FEED     = 60.0;
inline static constexpr double Z_RETRACT_FEED   = 800.0;
inline static constexpr bool   FILE_PER_TOOL    = true;
}

class GCodeExporter : public AbstractExporter
{
public:
    QString settingsFile() const override;
    QVector<Settings> defaultSettings() const override;
    bool save(const QString &fileName, const DrillDocument &document, const QVector<Settings> &settings) override;

private:
    void decodeFileName(const QString &fileName);
    void open(const QString &fileName = QString());
    void close();
    void exportTool(const DrillNode *toolNode);
    void exportHole(const DrillNode *holeNode, const QPointF &pos);

private:
    QString basePath_;
    QString baseName_;
    QFile file_;
    QTextStream out_;

    struct GCodeSettings {
        // double zToolChange;
        double zMove;
        double xyMoveFeed;
        double zDrillOffset;
        double zDrillFeed;
        double zRetractFeed;
        bool filePerTool;

        static GCodeSettings from(const QVector<Settings> &settings);
    };

    GCodeSettings settings_;
};



#endif // GCODEEXPORTER_H
