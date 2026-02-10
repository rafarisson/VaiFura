#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H

#include <QHash>
#include "Settings.h"

class SettingsReader
{
public:
    explicit SettingsReader(const QVector<Settings> &settings) {
        for (const auto &s : settings) {
            if (map_.contains(s.key))
                continue;
            map_.insert(s.key, &s);
        }
    }

    QVariant value(const QString &key, const QVariant &def = {}) const {
        auto it = map_.find(key);
        return it != map_.end() ? (*it)->value : def;
    }

    double number(const QString &key, double def = 0.0) const {
        return value(key, def).toDouble();
    }

    bool boolean(const QString &key, bool def = false) const {
        return value(key, def).toBool();
    }

private:
    QHash<QString, const Settings*> map_;
};

#endif // SETTINGSREADER_H
