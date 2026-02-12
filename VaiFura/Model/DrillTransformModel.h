#ifndef DRILLTRANSFORMMODEL_H
#define DRILLTRANSFORMMODEL_H

#include <QQmlEngine>
#include <QObject>
#include <QPointF>

class DrillTransformModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QPointF offset READ offset WRITE setOffset NOTIFY offsetChanged)
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(bool mirrorX READ mirrorX WRITE setMirrorX NOTIFY mirrorXChanged)
    Q_PROPERTY(bool mirrorY READ mirrorY WRITE setMirrorY NOTIFY mirrorYChanged)

public:
    explicit DrillTransformModel(QObject *parent = nullptr);

    QPointF offset() const { return offset_; }
    void setOffset(const QPointF &o);

    double rotation() const { return rotation_; }
    void setRotation(double rotation);

    bool mirrorX() const { return mirrorX_; }
    void setMirrorX(bool mirror);

    bool mirrorY() const { return mirrorY_; }
    void setMirrorY(bool mirror);

signals:
    void offsetChanged();
    void rotationChanged();
    void mirrorXChanged();
    void mirrorYChanged();

private:
    QPointF offset_ = {0, 0};
    double rotation_ = 0.0;
    bool mirrorX_ = false;
    bool mirrorY_ = false;
};


#endif // DRILLTRANSFORMMODEL_H
