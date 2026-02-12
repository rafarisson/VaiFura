#include <QFile>
#include <QTextStream>

#include "DrillDocumentModel.h"
#include "DrillDocument.h"
#include "DrillDocumentBuilder.h"
#include "DrillNode.h"
#include "DrillParser.h"

DrillDocumentModel::DrillDocumentModel(QObject *parent)
    : QObject{parent}
    , doc_{new DrillDocument()}
{
    connect(this, &DrillDocumentModel::drillCheckeStateChanged, this, &DrillDocumentModel::updateSelectedHoleCount);
}

void DrillDocumentModel::loadFromFile(const QString &filePath, DrillParser &parser)
{
    DrillDocumentBuilder builder(doc_);

    if (!filePath.isEmpty()) {
        QFile f(filePath);
        if (f.open(QIODevice::ReadOnly)) {
            QTextStream in(&f);
            parser.parse(in, builder);
            builder.build();
            f.close();
        }
    }

    updateSelectedHoleCount();

    emit documentContentChanged();
}

bool DrillDocumentModel::setCheckState(const DrillNode *node, Qt::CheckState newState)
{
    auto *n = const_cast<DrillNode*>(node);
    if (!n || !n->setCheckState(newState))
        return false;

    emit drillCheckeStateChanged();
    return true;
}

void DrillDocumentModel::updateSelectedHoleCount()
{
    int newCount = doc_->root()->checkedHoleCount();
    if (selectedHoleCount_ == newCount)
        return;

    selectedHoleCount_ = newCount;
    emit selectedHoleCountChanged();
}

