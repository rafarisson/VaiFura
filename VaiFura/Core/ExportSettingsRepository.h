#ifndef EXPORTSETTINGSREPOSITORY_H
#define EXPORTSETTINGSREPOSITORY_H

#include <QString>
#include <QVector>
#include "ExportSettings.h"

class ExportSettingsRepository
{
public:
    static void load(const QString &fileName, QVector<ExportSettings> *settings);
};

#endif // EXPORTSETTINGSREPOSITORY_H
