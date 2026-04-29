#include <QCoreApplication>
#include <QDir>
#include "VaiFuraSingleton.h"
#include "Machine.h"
#include "ExcellonDrillParser.h"
#include "DimensionOutline.h"
#include "SettingsRepository.h"
#include "SettingsReader.h"
#include "DrillDocumentExportPreparer.h"
#include "NoneOptimization.h"
#include "NearestNeighborOptimization.h"
#include "NearestNeighbor2OptOptimization.h"

VaiFuraSingleton::VaiFuraSingleton(QObject *parent)
    : QObject{parent}
    , documentModel_{new DrillDocumentModel(this)}
    , toolsModel_{new ToolListModel(this)}
    , holesModel_{new HoleListModel(this)}
    , drillTreeModel_{new DrillTreeModel(this)}
    , transformModel_{new DrillTransformModel(this)}
    , optimizationModel_{new OptimizationModel(this)}
    , machineSettingsModel_{new SettingsListModel(this)}
    , settingsModel_{new SettingsListModel(this)}
    , exporter_{new GCodeExporter}
{
    connect(documentModel_, &DrillDocumentModel::documentContentChanged, this, &VaiFuraSingleton::updateOptimizationPlan);
    connect(documentModel_, &DrillDocumentModel::drillCheckeStateChanged, this, &VaiFuraSingleton::updateOptimizationPlan);
    connect(transformModel_, &DrillTransformModel::transformChanged, this, &VaiFuraSingleton::updateOptimizationPlan);
    connect(optimizationModel_, &OptimizationModel::currentPanChanged, this, &VaiFuraSingleton::updateOptimizationPlan);

    toolsModel_->setModel(documentModel_);
    holesModel_->setModel(documentModel_);
    drillTreeModel_->setModel(documentModel_, transformModel_);

    optimizationModel_->addPlan(new NoneOptimization);
    optimizationModel_->addPlan(new NearestNeighborOptimization);
    optimizationModel_->addPlan(new NearestNeighbor2OptOptimization);

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

    DrillDocument optimizedDoc;
    optimizationModel_->generateOptimizedDrillDocument(optimizedDoc);

    DrillTransform realTransform = Machine::fixTransform(transformModel_->transform(), machineSettingsModel_->settings());
    DrillDocumentExportPreparer exporterDoc;
    exporterDoc.prepare(optimizedDoc, realTransform);

    SettingsReader setts(machineSettingsModel_->settings());
    exporter_->setUserStartupCode(QStringList() <<
                                  QString("G0 X%1 Y%2 ; Machine offset")
                                                       .arg(setts.number(MachineKeys::X_OFFSET, MachineDefault::X_OFFSET))
                                                       .arg(setts.number(MachineKeys::Y_OFFSET, MachineDefault::Y_OFFSET))
                                  );
    exporter_->save(output, exporterDoc.document(), settingsModel_->settings());
}

void VaiFuraSingleton::updateOptimizationPlan()
{
    optimizationModel_->optimize(documentModel_->document()->root(), transformModel_);
}

QString VaiFuraSingleton::resolvePath(const QString &fileName) const
{
    return QDir(QCoreApplication::applicationDirPath()).filePath(fileName);
}
