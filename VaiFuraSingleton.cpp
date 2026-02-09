#include <QCoreApplication>
#include <QDir>
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

void VaiFuraSingleton::setDocumentFileName(const QString &path)
{
    if (documentFileName_ == path)
        return;

    documentFileName_ = QUrl::fromUserInput(path).toLocalFile();
    emit documentFileNameChanged();

    ExcellonDrillParser parser;
    documentModel_->loadFromFile(documentFileName_, parser);
}
QString VaiFuraSingleton::resolvePath(const QString &fileName) const
{
    return QDir(QCoreApplication::applicationDirPath()).filePath(fileName);
}
