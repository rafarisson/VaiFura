#ifndef VAIFURASINGLETON_H
#define VAIFURASINGLETON_H

#include <QObject>
#include <QQmlEngine>

#include "DrillDocumentModel.h"
#include "ToolListModel.h"
#include "HoleListModel.h"
#include "DrillTreeModel.h"
#include "ExportSettingsListModel.h"

class VaiFuraSingleton : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(VaiFura)

    Q_PROPERTY(QString documentPath READ documentPath WRITE setDocumentPath NOTIFY documentPathChanged)
    Q_PROPERTY(DrillDocumentModel* model READ model CONSTANT FINAL)
    Q_PROPERTY(ToolListModel* toolsModel READ toolsModel CONSTANT FINAL)
    Q_PROPERTY(HoleListModel* holesModel READ holesModel CONSTANT FINAL)
    Q_PROPERTY(DrillTreeModel *drillsModel READ drillsModel CONSTANT FINAL)
    Q_PROPERTY(ExportSettingsListModel *exportSettingsModel READ exportSettingsModel CONSTANT FINAL)

public:
    explicit VaiFuraSingleton(QObject *parent = nullptr);

    QString documentPath() const { return documentPath_; }
    void setDocumentPath(const QString &path);

    DrillDocumentModel* model() const { return documentModel_; }
    ToolListModel* toolsModel() const { return toolsModel_; }
    HoleListModel* holesModel() const { return holesModel_; }
    DrillTreeModel* drillsModel() const { return drillTreeModel_; }
    ExportSettingsListModel* exportSettingsModel() const { return exportSettingsModel_; }

signals:
    void documentPathChanged();

private:
    QString documentPath_;

    DrillDocumentModel *documentModel_ = nullptr;
    ToolListModel *toolsModel_ = nullptr;
    HoleListModel *holesModel_ = nullptr;
    DrillTreeModel *drillTreeModel_ = nullptr;
    ExportSettingsListModel *exportSettingsModel_ = nullptr;
};

#endif // VAIFURASINGLETON_H
