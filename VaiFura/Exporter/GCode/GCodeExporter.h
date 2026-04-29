#ifndef GCODEEXPORTER_H
#define GCODEEXPORTER_H

#include <QFile>
#include <QTextStream>
#include "AbstractExporter.h"

class DrillNode;

namespace GCodeKeys {
inline static constexpr auto Z_TOOL_CHANGE  = "Z_TOOL_CHANGE";
inline static constexpr auto Z_MOVE         = "Z_MOVE";
inline static constexpr auto XY_MOVE_FEED   = "XY_MOVE_FEED";
inline static constexpr auto Z_DRILL_OFFSET = "Z_DRILL_OFFSET";
inline static constexpr auto Z_DRILL_FEED   = "Z_DRILL_FEED";
inline static constexpr auto Z_RETRACT_FEED = "Z_RETRACT_FEED";
inline static constexpr auto STARTUP_DELAY = "STARTUP_DELAY";
}

namespace GCodeDefault {
inline static constexpr double Z_TOOL_CHANGE    = 20.0;
inline static constexpr double Z_MOVE           = 1.0;
inline static constexpr double XY_MOVE_FEED     = 3000.0;
inline static constexpr double Z_DRILL_OFFSET   = -2.0;
inline static constexpr double Z_DRILL_FEED     = 60.0;
inline static constexpr double Z_RETRACT_FEED   = 800.0;
inline static constexpr double STARTUP_DELAY    = 3.0;
}

class GCodeExporter : public AbstractExporter
{
public:
    QString settingsFile() const override;
    QVector<Settings> defaultSettings() const override;

    void setUserStartupCode(const QStringList &commands);
    void setUserEndCode(const QStringList &commands);

    bool save(const QString &fileName, const DrillDocument *document, const QVector<Settings> &settings) override;

private:
    void decodeFileName(const QString &fileName);
    void open(const QString &fileName = QString());
    void close();
    void exportHeader();
    void exportIniti();
    void exportTool(const DrillNode *toolNode);
    void exportHole(const DrillNode *holeNode, const QPointF &pos);
    void exportToolChange();
    void gcodeFanOn();
    void gcodeFanOff();
    void gcodeSetHotEnd(uint value);
    void gcodeUser(const QStringList &commands);

private:
    const DrillDocument *document_ = nullptr;
    QStringList userStartupCode_;
    QStringList userEndCode_;

    QString basePath_;
    QString baseName_;
    QFile file_;
    QTextStream out_;
    int holeCount_;

    struct GCodeSettings {
        double zToolChange;
        double zMove;
        double xyMoveFeed;
        double zDrillOffset;
        double zDrillFeed;
        double zRetractFeed;
        double startupDelay;
        bool filePerTool;

        static GCodeSettings from(const QVector<Settings> &settings);
    };

    GCodeSettings settings_;
};



#endif // GCODEEXPORTER_H
