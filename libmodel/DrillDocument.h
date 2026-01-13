#ifndef DRILLDOCUMENT_H
#define DRILLDOCUMENT_H

#include <QtQml/qqml.h>
#include <QPointF>
#include <QObject>
#include "DrillModel.h"

class DrillDocument : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset NOTIFY offsetChanged)

public:
    explicit DrillDocument(QObject *parent = nullptr);

    QString path() const { return path_; }
    void setPath(const QString &newPath);
    QPointF offset() const { return offset_; }
    void setOffset(const QPointF &o);

    bool loadFile(const QString &path);
    DrillModel *model() const { return model_; }

signals:
    void changed();
    void pathChanged();
    void offsetChanged();

private:
    QString path_;
    DrillModel *model_ = nullptr;
    QPointF offset_{0, 0};
};

#endif // DRILLDOCUMENT_H
