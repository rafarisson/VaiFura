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

    settings.clear();

    const QJsonDocument json = QJsonDocument::fromJson(file.readAll());
    if (!json.isArray())
        return false;

    const QJsonArray array = json.array();

    for (const QJsonValue &v : array) {
        if (!v.isObject())
            continue;

        const QJsonObject obj = v.toObject();

        Settings s;
        s.key = obj.value("key").toString();
        s.label = obj.value("label").toString();
        s.description = obj.value("description").toString();
        s.unit = obj.value("unit").toString();
        s.value = obj.value("value").toVariant();
        s.type = obj.value("type").toInt(Settings::Number);

        settings.append(s);
    }

    return settings.size() > 0;
}

bool SettingsRepository::save(const QString &fileName, const QVector<Settings> &settings)
{
    QJsonArray array;

    for (const Settings &s : settings) {
        QJsonObject obj;
        obj["key"] = s.key;
        obj["label"] = s.label;
        obj["description"] = s.description;
        obj["unit"] = s.unit;
        obj["value"] = QJsonValue::fromVariant(s.value);
        obj["type"] = static_cast<int>(s.type);

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
