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

    Q_PROPERTY(QString documentFileName READ documentFileName WRITE setDocumentFileName NOTIFY documentFileNameChanged)

    Q_PROPERTY(DrillDocumentModel* model READ model CONSTANT FINAL)
    Q_PROPERTY(ToolListModel* toolsModel READ toolsModel CONSTANT FINAL)
    Q_PROPERTY(HoleListModel* holesModel READ holesModel CONSTANT FINAL)
    Q_PROPERTY(DrillTreeModel* drillsModel READ drillsModel CONSTANT FINAL)
    Q_PROPERTY(DrillTransformModel* transformModel READ transformModel CONSTANT FINAL)
    Q_PROPERTY(SettingsListModel* settingsModel READ settingsModel CONSTANT FINAL)

public:
    explicit VaiFuraSingleton(QObject *parent = nullptr);

    QString documentFileName() const { return documentFileName_; }
    void setDocumentFileName(const QString &path);

    DrillDocumentModel *model() const { return documentModel_; }
    ToolListModel *toolsModel() const { return toolsModel_; }
    HoleListModel *holesModel() const { return holesModel_; }
    DrillTreeModel *drillsModel() const { return drillTreeModel_; }
    DrillTransformModel *transformModel() const { return transformModel_; }
    SettingsListModel *settingsModel() const { return settingsModel_; }

    Q_INVOKABLE void save(const QString &path);

private:
    QString resolvePath(const QString &fileName) const;

signals:
    void documentFileNameChanged();

private:
    QString documentFileName_;

    DrillDocumentModel *documentModel_ = nullptr;
    ToolListModel *toolsModel_ = nullptr;
    HoleListModel *holesModel_ = nullptr;
    DrillTreeModel *drillTreeModel_ = nullptr;
    DrillTransformModel *transformModel_ = nullptr;
    SettingsListModel *settingsModel_ = nullptr;

    GCodeExporter *exporter_ = nullptr;
};

#endif // VAIFURASINGLETON_H
