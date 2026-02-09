#include "Settings.h"

QVariant SettingsHelper::find(const QVector<Settings> &settings, const QString &key, QVariant def)
{
    for (const Settings &s : settings) {
        if (s.key == key)
            return s.value;
    }
    return def;
}
