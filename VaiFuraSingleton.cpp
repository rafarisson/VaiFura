#include "VaiFuraSingleton.h"

VaiFuraSingleton::VaiFuraSingleton(QObject *parent)
    : QObject{parent}
    , documentModel_{new DrillDocumentModel(this)}
    , toolsModel_{new ToolListModel(this)}
    , holesModel_{new HoleListModel(this)}
    , drillTreeModel_{new DrillTreeModel(this)}
{
    documentModel_->setParser(&excellonParser_);

    connect(documentModel_, &DrillDocumentModel::changed, this, [=]() {
        toolsModel_->setDocument(documentModel_->document());
        holesModel_->setDocument(documentModel_->document());
        drillTreeModel_->setModel(documentModel_->document());
    });
}

void VaiFuraSingleton::setDocumentPath(const QString &path)
{
    if (documentPath_ == path)
        return;
    documentPath_ = path;
    emit documentPathChanged();

    documentModel_->loadFile(documentPath_);
}
