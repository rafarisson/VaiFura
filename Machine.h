#ifndef MACHINE_H
#define MACHINE_H

#include <QObject>
#include "Settings.h"
#include "DrillTransform.h"

namespace MachineKeys {
inline static constexpr auto X_OFFSET  = "X_OFFSET";
inline static constexpr auto Y_OFFSET  = "Y_OFFSET";
};

namespace MachineDefault {
inline static constexpr double X_OFFSET  = 5.0;
inline static constexpr double Y_OFFSET  = 13.0;
};

namespace Machine {
QString settingsFile();
QVector<Settings> defaultSettings();
DrillTransform fixTransform(const DrillTransform *userTransform, const QVector<Settings> &machineSettings);
};

#endif // MACHINE_H
