#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "Settings.h"
#include "DrillTransform.h"

namespace Machine {

QString settingsFile();
QVector<Settings> defaultSettings();
DrillTransform fixTransform(const DrillTransform *userTransform, const QVector<Settings> &machineSettings);

};

#endif // MACHINE_H
