#include <QCoreApplication>
#include <QDir>
#include "VaiFuraSingleton.h"
#include "Machine.h"
#include "ExcellonDrillParser.h"
#include "DimensionOutline.h"
#include "SettingsRepository.h"
#include "DrillDocumentExportPreparer.h"

VaiFuraSingleton::VaiFuraSingleton(QObject *parent)
    : QObject{parent}
    , documentModel_{new DrillDocumentModel(this)}
    , toolsModel_{new ToolListModel(this)}
    , holesModel_{new HoleListModel(this)}
    , drillTreeModel_{new DrillTreeModel(this)}
    , transformModel_{new DrillTransformModel(this)}
    , machineSettingsModel_{new SettingsListModel(this)}
    , settingsModel_{new SettingsListModel(this)}
    , exporter_{new GCodeExporter}
{
    toolsModel_->setModel(documentModel_);
    holesModel_->setModel(documentModel_);
    drillTreeModel_->setModel(documentModel_, transformModel_);

    QVector<Settings> machineSettings = Machine::defaultSettings();
    SettingsRepository::load(resolvePath(Machine::settingsFile()), machineSettings);
    machineSettingsModel_->setSettings(machineSettings);

    QVector<Settings> exporterSettings = exporter_->defaultSettings();
    SettingsRepository::load(resolvePath(exporter_->settingsFile()), exporterSettings);
    settingsModel_->setSettings(exporterSettings);
}

void VaiFuraSingleton::setDrillDocumentFileName(const QString &path)
{
    if (drillDocumentFileName_ == path)
        return;

    drillDocumentFileName_ = QUrl::fromUserInput(path).toLocalFile();
    emit drillDocumentFileNameChanged();

    ExcellonDrillParser parser;
    documentModel_->loadDrill(drillDocumentFileName_, parser);
}

void VaiFuraSingleton::setProfileDocumentFileName(const QString &path)
{
    if (profileDocumentFileName_ == path)
        return;

    profileDocumentFileName_ = QUrl::fromUserInput(path).toLocalFile();
    emit profileDocumentFileNameChanged();

    DimensionOutline parser;
    documentModel_->loadProfile(profileDocumentFileName_, parser);
}

void VaiFuraSingleton::save(const QString &path)
{
    if (machineSettingsModel_->isModified())
        SettingsRepository::save(resolvePath(Machine::settingsFile()), machineSettingsModel_->settings());

    if (settingsModel_->isModified())
        SettingsRepository::save(resolvePath(exporter_->settingsFile()), settingsModel_->settings());

    QString fn = QFileInfo(drillDocumentFileName_).fileName();
    QString output = QUrl::fromUserInput(QDir(path).filePath(fn)).toLocalFile();

    auto realTransform = Machine::fixTransform(transformModel_->transform(), machineSettingsModel_->settings());

    DrillDocumentExportPreparer exporterDoc;
    exporterDoc.prepare(*documentModel_->document(), realTransform);

    exporter_->save(output, exporterDoc.document(), settingsModel_->settings());
}

QString VaiFuraSingleton::resolvePath(const QString &fileName) const
{
    return QDir(QCoreApplication::applicationDirPath()).filePath(fileName);
}
