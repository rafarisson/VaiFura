#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <cmath>
#include "ProfileRenderer.h"
#include "BoardProfile.h"
#include "DrillTransformModel.h"
#include "ViewportTransform.h"

void ProfileRenderer::build(QSGNode *root,
                            const BoardProfile *profile,
                            const DrillTransformModel *transform,
                            const ViewportTransform &vp,
                            const QPointF &delta)
{
    if (!profile || profile->paths().isEmpty())
        return;

    for (const BoardPath &path : profile->paths())
    {
        root->appendChildNode(
            createGeometryForPath(path, transform, vp, delta, 2.0, Qt::yellow)
            );
    }
}

QSGGeometryNode *ProfileRenderer::createGeometryForPath(const BoardPath &path,
                                                        const DrillTransformModel *transform,
                                                        const ViewportTransform &vp,
                                                        const QPointF &delta,
                                                        double thickness,
                                                        const QColor &color)
{
    int pointCount = path.points.size();

    if (pointCount < 2)
        return nullptr;

    QSGGeometry *geometry = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(),
        pointCount
        );

    geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
    geometry->setLineWidth(thickness);

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    for (int i = 0; i < pointCount; ++i)
    {
        const BoardPoint &pt = path.points[i];

        QPointF p(pt.x, pt.y);

        if (transform)
            p = transform->transform()->apply(p);


        p += delta;
        p = vp.toScreen(p);

        vertices[i].set(p.x(), p.y());
    }

    auto *material = new QSGFlatColorMaterial();
    material->setColor(color);

    QSGGeometryNode *node = new QSGGeometryNode();
    node->setGeometry(geometry);
    node->setMaterial(material);

    node->setFlag(QSGNode::OwnsGeometry);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}