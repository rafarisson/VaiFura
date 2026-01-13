#include <QFile>
#include <QTextStream>
#include "DrillDocument.h"
#include "ExcellonParser.h"

DrillDocument::DrillDocument(QObject *parent)
    : QObject{parent}
{
    model_ = new DrillModel;
}

void DrillDocument::setPath(const QString &newPath)
{
    if (path_ == newPath)
        return;

    path_ = newPath;
    emit pathChanged();

    loadFile(path_);
}

void DrillDocument::setOffset(const QPointF &o)
{
    if (offset_ == o)
        return;
    offset_ = o;
    emit offsetChanged();
}

bool DrillDocument::loadFile(const QString &path)
{
    model_->clear();

    QFile f(path);
    if (f.open(QIODevice::ReadOnly)) {
        QTextStream in(&f);
        ExcellonParser parser;
        *model_ = std::move(parser.parse(in));
        f.close();
    }

    emit changed();
    return true;
}
