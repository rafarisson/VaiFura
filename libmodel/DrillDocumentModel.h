#ifndef DRILLDOCUMENTMODEL_H
#define DRILLDOCUMENTMODEL_H

#include <QtQml/qqml.h>
#include <QPointF>
#include <QObject>
#include <QTextStream>

class DrillDocument;

class DrillDocumentModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(QPointF offset READ offset WRITE setOffset NOTIFY offsetChanged)

public:
    explicit DrillDocumentModel(QObject *parent = nullptr);

    const DrillDocument *document() const { return doc_; }
    void setDocument(DrillDocument *newDocument);

    QPointF offset() const { return offset_; }
    void setOffset(const QPointF &o);

signals:
    void documentChanged();
    void offsetChanged();
    void drillCheckeStateChanged();

private:
    const DrillDocument *doc_ = nullptr;
    QPointF offset_{0, 0};
};

#endif // DRILLDOCUMENTMODEL_H
