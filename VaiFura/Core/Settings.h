#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QVariant>

class Settings
{
public:
    enum Types {
        Number = 0,
        Text,
        Boolean
    };

    const QString key;
    const QString label;
    const QString description;
    const QString unit;
    QVariant value;
    const int type;
};

namespace SettingsHelper {
QVariant find(const QVector<Settings> &settings, const QString &key, QVariant def = {});
}

#endif // SETTINGS_H
