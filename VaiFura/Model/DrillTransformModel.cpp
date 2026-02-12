#include "DrillTransformModel.h"

DrillTransformModel::DrillTransformModel(QObject *parent)
    : QObject{parent}
{
}

void DrillTransformModel::setOffset(const QPointF &o)
{
    if (offset_ == o)
        return;
    offset_ = o;
    emit offsetChanged();
}

void DrillTransformModel::setRotation(double rotation)
{

}

void DrillTransformModel::setMirrorX(bool mirror)
{
    if (mirrorX_ == mirror)
        return;
    mirrorX_ = mirror;
    mirrorXChanged();
}

void DrillTransformModel::setMirrorY(bool mirror)
{
    if (mirrorY_ == mirror)
        return;
    mirrorY_ = mirror;
    mirrorYChanged();
}
