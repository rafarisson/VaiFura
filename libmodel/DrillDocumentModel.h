#ifndef DRILLDOCUMENTMODEL_H
#define DRILLDOCUMENTMODEL_H

#include <QtQml/qqml.h>
#include <QPointF>
#include <QObject>
#include <QTextStream>

class DrillNode;
class DrillDocument;
class DrillParser;

class DrillDocumentModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(int selectedHoleCount READ selectedHoleCount NOTIFY selectedHoleCountChanged)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset NOTIFY offsetChanged)

public:
    explicit DrillDocumentModel(QObject *parent = nullptr);

    const DrillDocument *document() const { return doc_; }
    void loadFromFile(const QString &filePath, DrillParser &parser);

    int selectedHoleCount() const { return selectedHoleCount_; }

    QPointF offset() const { return offset_; }
    void setOffset(const QPointF &o);

    bool setCheckState(const DrillNode *node, Qt::CheckState newState);

private:
    int calculateSelectedHoleDelta(const DrillNode *node);
    void setSelectedHoleCount(int newCount);

signals:
    void documentContentChanged();
    void drillCheckeStateChanged();
    void selectedHoleCountChanged();
    void offsetChanged();

private:
    DrillDocument *doc_ = nullptr;
    int selectedHoleCount_ = {0};
    QPointF offset_{0, 0};
};

#endif // DRILLDOCUMENTMODEL_H
