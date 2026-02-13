#ifndef ORIGINRENDERER_H
#define ORIGINRENDERER_H

#include <QSGNode>

class DrillTransformModel;
class ViewportTransform;

class OriginRenderer
{
public:
    void build(QSGNode *root, const DrillTransformModel *transform, const ViewportTransform &vp);
};

#endif // ORIGINRENDERER_H
