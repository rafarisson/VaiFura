#ifndef SETTINGSREPOSITORY_H
#define SETTINGSREPOSITORY_H

#include <QString>
#include <QVector>
#include "Settings.h"

class SettingsRepository
{
public:
    static bool load(const QString &fileName, QVector<Settings> *settings);
    static bool save(const QString &fileName, const QVector<Settings> *settings);
};

#endif // SETTINGSREPOSITORY_H
