#include "VaiFuraSingleton.h"
#include "ExcellonDrillParser.h"

VaiFuraSingleton::VaiFuraSingleton(QObject *parent)
    : QObject{parent}
    , documentModel_{new DrillDocumentModel(this)}
    , toolsModel_{new ToolListModel(this)}
    , holesModel_{new HoleListModel(this)}
    , drillTreeModel_{new DrillTreeModel(this)}
    , settingsModel_{new SettingsListModel(this)}
{
    toolsModel_->setModel(documentModel_);
    holesModel_->setModel(documentModel_);
    drillTreeModel_->setModel(documentModel_);
    settingsModel_->load(QDir(QCoreApplication::applicationDirPath()).filePath("settings.json"));
}

void VaiFuraSingleton::setDocumentPath(const QString &path)
{
    if (documentPath_ == path)
        return;

    documentPath_ = path;
    emit documentPathChanged();

    ExcellonDrillParser parser;
    documentModel_->loadFromFile(path, parser);
}
