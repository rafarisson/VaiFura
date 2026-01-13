#include "VaiFuraSingleton.h"

VaiFuraSingleton::VaiFuraSingleton(QObject *parent)
    : QObject{parent}
    , drillDoc_{new DrillDocument(this)}
    , toolListModel_{new ToolListModel(this)}
    , drillListModel_{new DrillListModel(this)}
    , drillTreeModel_{new DrillTreeModel(this)}
{
    connect(drillDoc_, &DrillDocument::changed, this, [=]() {
        toolListModel_->setModel(drillDoc_->model());
        drillListModel_->setModel(drillDoc_->model());
        drillTreeModel_->setModel(drillDoc_->model());
    });
}
