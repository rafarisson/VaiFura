#include <QCoreApplication>
#include <QDir>
#include "VaiFuraSingleton.h"
#include "ExcellonDrillParser.h"
#include "SettingsRepository.h"
#include "DrillDocumentExportPreparer.h"

VaiFuraSingleton::VaiFuraSingleton(QObject *parent)
    : QObject{parent}
    , documentModel_{new DrillDocumentModel(this)}
    , toolsModel_{new ToolListModel(this)}
    , holesModel_{new HoleListModel(this)}
    , drillTreeModel_{new DrillTreeModel(this)}
    , settingsModel_{new SettingsListModel(this)}
    , exporter_{new GCodeExporter}
{
    toolsModel_->setModel(documentModel_);
    holesModel_->setModel(documentModel_);
    drillTreeModel_->setModel(documentModel_);

    QVector<Settings> exporterSettings;
    if (!SettingsRepository::load(resolvePath(exporter_->settingsFile()), exporterSettings))
        exporterSettings = exporter_->defaultSettings();
    settingsModel_->setSettings(exporterSettings);
}

void VaiFuraSingleton::setDocumentFileName(const QString &path)
{
    if (documentFileName_ == path)
        return;

    documentFileName_ = QUrl::fromUserInput(path).toLocalFile();
    emit documentFileNameChanged();

    ExcellonDrillParser parser;
    documentModel_->loadFromFile(documentFileName_, parser);
}

void VaiFuraSingleton::save(const QString &path)
{
    SettingsRepository::save(resolvePath(exporter_->settingsFile()), settingsModel_->settings());

    QString fn = QFileInfo(documentFileName_).fileName();
    QString output = QUrl::fromUserInput(QDir(path).filePath(fn)).toLocalFile();

    DrillDocumentExportPreparer documentTransformer;
    documentTransformer.prepare(*documentModel_->document(), documentModel_->offset());

    exporter_->save(output, *documentTransformer.document(), settingsModel_->settings());
}

QString VaiFuraSingleton::resolvePath(const QString &fileName) const
{
    return QDir(QCoreApplication::applicationDirPath()).filePath(fileName);
}
