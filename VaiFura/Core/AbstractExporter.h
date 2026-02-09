#ifndef ABSTRACTEXPORTER_H
#define ABSTRACTEXPORTER_H

#include "Settings.h"

class DrillDocument;

class AbstractExporter
{
public:
    AbstractExporter() = default;
    virtual ~AbstractExporter() = default;

    virtual QString settingsFile() const = 0;
    virtual QVector<Settings> defaultSettings() const;
    virtual bool save(const QString &fileName, const DrillDocument *document, const QVector<Settings> &settings) = 0;
};

#endif // ABSTRACTEXPORTER_H
