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

    QString key;
    QString label;
    QString description;
    QString unit;
    QVariant value;
    int type;
};

namespace SettingsHelper {
QVariant find(const QVector<Settings> &settings, const QString &key, QVariant def = {});
}

#endif // SETTINGS_H
