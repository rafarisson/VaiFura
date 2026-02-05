#ifndef EXPORTSETTINGS_H
#define EXPORTSETTINGS_H

#include <QString>
#include <QVariant>

class ExportSettings
{
public:
    QString key;
    QString label;
    QString description;
    QString unit;
    QVariant value;
};

#endif // EXPORTSETTINGS_H
