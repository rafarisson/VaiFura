#ifndef DRILLEXPORTER_H
#define DRILLEXPORTER_H

#include <QString>

class DrillDocument;
class ExportSettings;

class DrillExporter
{
public:
    virtual ~DrillExporter() = default;
    virtual bool save(const QString &fileName,
                      const DrillDocument &document,
                      const ExportSettings &settings);
};

#endif // DRILLEXPORTER_H
