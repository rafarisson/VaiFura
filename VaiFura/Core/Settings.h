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

#endif // SETTINGS_H
