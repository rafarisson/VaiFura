#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "SettingsRepository.h"

bool SettingsRepository::load(const QString &fileName, QVector<Settings> &settings)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    const QJsonDocument json = QJsonDocument::fromJson(file.readAll());
    if (!json.isArray())
        return false;

    const QJsonArray array = json.array();
    QSet<QString> seenKeys;

    for (const QJsonValue &v : array) {
        if (!v.isObject())
            continue;

        const QJsonObject obj = v.toObject();
        const QString key = obj.value("key").toString();

        if (seenKeys.contains(key))
            continue;

        auto it = std::find_if(settings.begin(), settings.end(), [&](const Settings &s) {
            return s.key == key;
        });
        if (it == settings.end())
            continue;

        seenKeys.insert(key);
        it->value = obj.value("value").toVariant();
    }

    return settings.size() > 0;
}

bool SettingsRepository::save(const QString &fileName, const QVector<Settings> &settings)
{
    QJsonArray array;

    for (const Settings &s : settings) {
        QJsonObject obj;
        obj["key"] = s.key;
        obj["value"] = QJsonValue::fromVariant(s.value);
        array.append(obj);
    }

    if (array.empty())
        return false;

    QFile file(QDir::toNativeSeparators(fileName));
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument doc(array);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    return true;
}
