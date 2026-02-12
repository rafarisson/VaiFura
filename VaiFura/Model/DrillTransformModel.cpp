#include "DrillTransformModel.h"

DrillTransformModel::DrillTransformModel(QObject *parent)
    : QObject{parent}
    , transform_{new DrillTransform}
{
    connect(this, &DrillTransformModel::offsetChanged, this, &DrillTransformModel::transformChanged);
    connect(this, &DrillTransformModel::rotationChanged, this, &DrillTransformModel::transformChanged);
    connect(this, &DrillTransformModel::mirrorXChanged, this, &DrillTransformModel::transformChanged);
    connect(this, &DrillTransformModel::mirrorYChanged, this, &DrillTransformModel::transformChanged);
}

void DrillTransformModel::setPivot(const QPointF &p)
{
    if (transform_->pivot == p)
        return;
    transform_->pivot = p;
    emit pivotChanged();
}

void DrillTransformModel::setOffset(const QPointF &o)
{
    if (transform_->offset == o)
        return;
    transform_->offset = o;
    emit offsetChanged();
}

void DrillTransformModel::setRotation(double rotation)
{
    double deg = std::fmod(rotation, 360.0);
    if (qFuzzyCompare(transform_->rotation, deg))
        return;
    transform_->rotation = deg;
    emit rotationChanged();
}

void DrillTransformModel::setMirrorX(bool mirror)
{
    if (transform_->mirrorX == mirror)
        return;
    transform_->mirrorX = mirror;
    mirrorXChanged();
}

void DrillTransformModel::setMirrorY(bool mirror)
{
    if (transform_->mirrorY == mirror)
        return;
    transform_->mirrorY = mirror;
    mirrorYChanged();
}

