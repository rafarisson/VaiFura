#include <QFile>
#include <QTextStream>
#include "DrillParser.h"
#include "DrillDocument.h"
#include "DrillDocumentModel.h"
#include "DrillDocumentBuilder.h"
#include "DrillTreeDocumentBuilder.h"

DrillDocumentModel::DrillDocumentModel(QObject *parent)
    : QObject{parent}
{}

void DrillDocumentModel::setOffset(const QPointF &o)
{
    if (offset_ == o)
        return;
    offset_ = o;
    emit offsetChanged();
}

void DrillDocumentModel::setParser(DrillParser *parser)
{
    parser_ = parser;
}

void DrillDocumentModel::loadFile(const QString &path)
{
    doc_.reset();

    if (parser_) {
        QFile f(path);

        if (f.open(QIODevice::ReadOnly)) {
            QTextStream in(&f);
            DrillDocumentBuilder builder;
            parser_->parse(in, builder);
            doc_ = builder.build();
            f.close();
        }
    }

    DrillTreeDocumentBuilder treeBuilder;
    treeBuilder.build(treeDoc_, doc_);

    emit changed();
}
