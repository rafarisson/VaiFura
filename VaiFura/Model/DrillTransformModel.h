#ifndef DRILLTRANSFORMMODEL_H
#define DRILLTRANSFORMMODEL_H

#include <QQmlEngine>
#include <QObject>
#include <QPointF>
#include "DrillTransform.h"

class DrillTransformModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QPointF origin READ origin WRITE setOrigin NOTIFY originChanged)
    Q_PROPERTY(QPointF pivot READ pivot WRITE setPivot NOTIFY pivotChanged)
    Q_PROPERTY(QPointF offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(bool mirrorX READ mirrorX WRITE setMirrorX NOTIFY mirrorXChanged)
    Q_PROPERTY(bool mirrorY READ mirrorY WRITE setMirrorY NOTIFY mirrorYChanged)

public:
    explicit DrillTransformModel(QObject *parent = nullptr);

    const DrillTransform *transform() const { return transform_; }

    QPointF origin() const { return transform_->origin; }
    void setOrigin(const QPointF &p);

    QPointF pivot() const { return transform_->pivot; }
    void setPivot(const QPointF &p);

    QPointF offset() const { return transform_->offset; }
    void setOffset(const QPointF &o);

    double rotation() const { return transform_->rotation; }
    void setRotation(double rotation);

    bool mirrorX() const { return transform_->mirrorX; }
    void setMirrorX(bool mirror);

    bool mirrorY() const { return transform_->mirrorY; }
    void setMirrorY(bool mirror);

signals:
    void transformChanged();
    void originChanged();
    void pivotChanged();
    void offsetChanged();
    void rotationChanged();
    void mirrorXChanged();
    void mirrorYChanged();

private:
    DrillTransform *transform_ = nullptr;
};


#endif // DRILLTRANSFORMMODEL_H
