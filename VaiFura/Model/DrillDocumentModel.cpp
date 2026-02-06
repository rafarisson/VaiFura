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
{}

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

    setSelectedHoleCount(doc_->holes().count());

    emit documentContentChanged();
}

void DrillDocumentModel::setOffset(const QPointF &o)
{
    if (offset_ == o)
        return;
    offset_ = o;
    emit offsetChanged();
}

bool DrillDocumentModel::setCheckState(const DrillNode *node, Qt::CheckState newState)
{
    auto *n = const_cast<DrillNode*>(node);
    if (!n || !n->setCheckState(newState))
        return false;

    int delta = calculateSelectedHoleDelta(node);
    setSelectedHoleCount(selectedHoleCount_ + delta);

    emit drillCheckeStateChanged();
    return true;
}

int DrillDocumentModel::calculateSelectedHoleDelta(const DrillNode *node)
{
    if (!node)
        return 0;
    if (node->type() == DrillNode::Type::IsHole)
        return node->isChecked() ? 1 : -1;

    int count = 0;
    for (int i = 0; i < node->childCount(); ++i)
        count += calculateSelectedHoleDelta(node->child(i));
    return count;
}

void DrillDocumentModel::setSelectedHoleCount(int newCount)
{
    if (selectedHoleCount_ == newCount)
        return;

    selectedHoleCount_ = newCount;
    emit selectedHoleCountChanged();
}

