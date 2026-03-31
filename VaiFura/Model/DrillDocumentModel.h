#ifndef DRILLDOCUMENTMODEL_H
#define DRILLDOCUMENTMODEL_H

#include <QQmlEngine>
#include <QPointF>
#include <QObject>
#include <QTextStream>

class DrillNode;
class DrillDocument;
class DrillParser;
class BoardProfile;
class BoardProfileParser;

class DrillDocumentModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")

    Q_PROPERTY(int selectedHoleCount READ selectedHoleCount NOTIFY selectedHoleCountChanged)

public:
    explicit DrillDocumentModel(QObject *parent = nullptr);

    const DrillDocument *document() const { return doc_; }
    const BoardProfile *profile() const { return profile_; }

    void loadDrill(const QString &filePath, DrillParser &parser);
    void loadProfile(const QString &filePath, BoardProfileParser &parser);

    int selectedHoleCount() const { return selectedHoleCount_; }

    bool setCheckState(const DrillNode *node, Qt::CheckState newState);

private:
    void updateSelectedHoleCount();

signals:
    void documentContentChanged();
    void profileChanged();
    void drillCheckeStateChanged();
    void selectedHoleCountChanged();

private:
    DrillDocument *doc_ = nullptr;
    BoardProfile *profile_ = nullptr;
    int selectedHoleCount_ = {0};
};

#endif // DRILLDOCUMENTMODEL_H
