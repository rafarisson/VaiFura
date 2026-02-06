#ifndef DRILLEXPORTER_H
#define DRILLEXPORTER_H

#include <QString>

class DrillDocument;
class Settings;

class DrillExporter
{
public:
    virtual ~DrillExporter() = default;
    virtual bool save(const QString &fileName,
                      const DrillDocument &document,
                      const Settings &settings);
};

#endif // DRILLEXPORTER_H
