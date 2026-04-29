#include "Machine.h"
#include "SettingsReader.h"

QString Machine::settingsFile()
{
    return "machine.json";
}

QVector<Settings> Machine::defaultSettings() {
    return {
            Settings{
                MachineKeys::X_OFFSET,
                "X Offset",
                "Defines the offset between the machine origin (0,0) and the actual drilling start position on the X axis.",
                "mm",
                MachineDefault::X_OFFSET,
                Settings::Number
            },
            Settings{
                MachineKeys::Y_OFFSET,
                "Y Offset",
                "Defines the offset between the machine origin (0,0) and the actual drilling start position on the Y axis.",
                "mm",
                MachineDefault::Y_OFFSET,
                Settings::Number
            }
    };
}

DrillTransform Machine::fixTransform(const DrillTransform *userTransform, const QVector<Settings> &machineSettings) {
    DrillTransform t;

    if (userTransform)
        t = *userTransform;

    if (!machineSettings.isEmpty()) {
        SettingsReader setts(machineSettings);
        QPointF userOffset(setts.number(MachineKeys::X_OFFSET, MachineDefault::X_OFFSET),
                           setts.number(MachineKeys::Y_OFFSET, MachineDefault::Y_OFFSET));
        t.offset += userOffset;
    }

    return t;
}
