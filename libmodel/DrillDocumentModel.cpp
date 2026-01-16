#include "DrillDocumentModel.h"
#include "DrillDocument.h"
#include "DrillTreeModel.h"

DrillDocumentModel::DrillDocumentModel(QObject *parent)
    : QObject{parent}
    , doc_{new DrillDocument()}
{}

void DrillDocumentModel::setDocument(DrillDocument *newDocument)
{
    doc_ = newDocument;
    emit documentChanged();
}

void DrillDocumentModel::setOffset(const QPointF &o)
{
    if (offset_ == o)
        return;
    offset_ = o;
    emit offsetChanged();
}

