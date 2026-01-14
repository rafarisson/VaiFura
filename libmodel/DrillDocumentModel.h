#ifndef DRILLDOCUMENTMODEL_H
#define DRILLDOCUMENTMODEL_H

#include <QtQml/qqml.h>
#include <QPointF>
#include <QObject>
#include "DrillDocument.h"
#include "DrillTreeDocument.h"

class DrillParser;

class DrillDocumentModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(QPointF offset READ offset WRITE setOffset NOTIFY offsetChanged)

public:
    explicit DrillDocumentModel(QObject *parent = nullptr);

    QPointF offset() const { return offset_; }
    void setOffset(const QPointF &o);

    void setParser(DrillParser *parser);
    void loadFile(const QString &path);
    const DrillDocument *document() const { return &doc_; }
    const DrillTreeDocument *treeDocument() const { return &treeDoc_; }

signals:
    void changed();
    void offsetChanged();

private:
    DrillParser *parser_ = nullptr;
    DrillDocument doc_;
    DrillTreeDocument treeDoc_;
    QPointF offset_{0, 0};
};

#endif // DRILLDOCUMENTMODEL_H
