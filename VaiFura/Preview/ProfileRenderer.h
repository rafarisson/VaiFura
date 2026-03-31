#ifndef PROFILERENDERER_H
#define PROFILERENDERER_H

#include <QSGNode>

class BoardPath;
class BoardProfile;
class DrillTransformModel;
class ViewportTransform;

class ProfileRenderer
{
public:
    void build(QSGNode *root,
               const BoardProfile *profile,
               const DrillTransformModel *transform,
               const ViewportTransform &vp,
               const QPointF &delta);

private:
    QSGGeometryNode *createGeometryForPath(const BoardPath &path,
                                           const DrillTransformModel *transform,
                                           const ViewportTransform &vp,
                                           const QPointF &delta,
                                           double thickness,
                                           const QColor &color);
};

#endif //
