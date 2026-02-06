#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "ExportSettingsRepository.h"

void ExportSettingsRepository::load(const QString &fileName, QVector<ExportSettings> *settings)
{
    if (!settings)
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    settings->clear();

    const QJsonDocument json = QJsonDocument::fromJson(file.readAll());
    if (!json.isArray())
        return;

    const QJsonArray array = json.array();
    for (const QJsonValue &v : array) {
        if (!v.isObject())
            continue;

        const QJsonObject obj = v.toObject();

        ExportSettings s;
        s.key = obj.value("key").toString();
        s.label = obj.value("label").toString();
        s.description = obj.value("description").toString();
        s.unit = obj.value("unit").toString();
        s.value = obj.value("value").toVariant();
        s.type = obj.value("type").toInt(ExportSettings::Number);

        settings->append(s);
    }
}
