#include <QFile>
#include <QTextStream>

#include "VaiFuraSingleton.h"
#include "DrillDocumentBuilder.h"
#include "ExcellonDrillParser.h"

VaiFuraSingleton::VaiFuraSingleton(QObject *parent)
    : QObject{parent}
    , documentModel_{new DrillDocumentModel(this)}
    , toolsModel_{new ToolListModel(this)}
    , holesModel_{new HoleListModel(this)}
    , drillTreeModel_{new DrillTreeModel(this)}
{
    connect(documentModel_, &DrillDocumentModel::documentChanged, this, [=]() {
        toolsModel_->setModel(documentModel_->document());
        holesModel_->setModel(documentModel_->document());
        drillTreeModel_->setModel(documentModel_->document());
    });

    // connect(drillTreeModel_, &DrillTreeModel::dataChanged, [=](const QModelIndex &topLeft,
    //                                                            const QModelIndex &bottomRight,
    //                                                            const QList<int> &roles) {
    //     if (roles.contains(DrillTreeModel::CheckStateRole)) {

    //     }
    // });

    connect(drillTreeModel_, &DrillTreeModel::dataChanged,
            documentModel_, &DrillDocumentModel::drillCheckeStateChanged);
}

void VaiFuraSingleton::setDocumentPath(const QString &path)
{
    if (documentPath_ == path)
        return;
    documentPath_ = path;
    emit documentPathChanged();

    DrillDocumentBuilder builder(&doc_);

    QFile f(path);
    if (f.open(QIODevice::ReadOnly)) {
        QTextStream in(&f);
        ExcellonDrillParser parser;
        parser.parse(in, builder);
        builder.build();
        f.close();
    }

    documentModel_->setDocument(&doc_);
}
