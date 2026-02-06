#ifndef EXPORTSETTINGS_H
#define EXPORTSETTINGS_H

#include <QString>
#include <QVariant>

class ExportSettings
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

#endif // EXPORTSETTINGS_H
