#ifndef VAIFURASINGLETON_H
#define VAIFURASINGLETON_H

#include <QObject>
#include <QQmlEngine>

#include "DrillDocumentModel.h"
#include "ToolListModel.h"
#include "HoleListModel.h"
#include "DrillTreeModel.h"
#include "DrillTransformModel.h"
#include "SettingsListModel.h"
#include "GCodeExporter.h"

class VaiFuraSingleton : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(VaiFura)

    Q_PROPERTY(QString drillDocumentFileName READ drillDocumentFileName WRITE setDrillDocumentFileName NOTIFY drillDocumentFileNameChanged)
    Q_PROPERTY(QString profileDocumentFileName READ profileDocumentFileName WRITE setProfileDocumentFileName NOTIFY profileDocumentFileNameChanged)

    Q_PROPERTY(DrillDocumentModel* model READ model CONSTANT FINAL)
    Q_PROPERTY(ToolListModel* toolsModel READ toolsModel CONSTANT FINAL)
    Q_PROPERTY(HoleListModel* holesModel READ holesModel CONSTANT FINAL)
    Q_PROPERTY(DrillTreeModel* drillsModel READ drillsModel CONSTANT FINAL)
    Q_PROPERTY(DrillTransformModel* transformModel READ transformModel CONSTANT FINAL)

    Q_PROPERTY(SettingsListModel* machineSettingsModel READ machineSettingsModel CONSTANT FINAL)
    Q_PROPERTY(SettingsListModel* settingsModel READ settingsModel CONSTANT FINAL)

public:
    explicit VaiFuraSingleton(QObject *parent = nullptr);

    QString drillDocumentFileName() const { return drillDocumentFileName_; }
    void setDrillDocumentFileName(const QString &path);

    QString profileDocumentFileName() const { return profileDocumentFileName_; }
    void setProfileDocumentFileName(const QString &path);

    DrillDocumentModel *model() const { return documentModel_; }
    ToolListModel *toolsModel() const { return toolsModel_; }
    HoleListModel *holesModel() const { return holesModel_; }
    DrillTreeModel *drillsModel() const { return drillTreeModel_; }
    DrillTransformModel *transformModel() const { return transformModel_; }
    SettingsListModel *machineSettingsModel() const { return machineSettingsModel_; }
    SettingsListModel *settingsModel() const { return settingsModel_; }

    Q_INVOKABLE void save(const QString &path);

private:
    QString resolvePath(const QString &fileName) const;

signals:
    void drillDocumentFileNameChanged();
    void profileDocumentFileNameChanged();

private:
    QString drillDocumentFileName_;
    QString profileDocumentFileName_;

    DrillDocumentModel *documentModel_ = nullptr;
    ToolListModel *toolsModel_ = nullptr;
    HoleListModel *holesModel_ = nullptr;
    DrillTreeModel *drillTreeModel_ = nullptr;
    DrillTransformModel *transformModel_ = nullptr;

    SettingsListModel *machineSettingsModel_ = nullptr;
    SettingsListModel *settingsModel_ = nullptr;

    GCodeExporter *exporter_ = nullptr;
};

#endif // VAIFURASINGLETON_H
