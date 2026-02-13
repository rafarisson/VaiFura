#include "OriginRenderer.h"
#include "DrillTransformModel.h"
#include "ViewportTransform.h"
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

void OriginRenderer::build(QSGNode *root, const DrillTransformModel *transform, const ViewportTransform &vp)
{
    QPointF o = vp.toScreen(transform ? transform->origin() : QPointF{0, 0});

    auto *geom = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(), 4);
    geom->setDrawingMode(QSGGeometry::DrawLines);

    auto *v = geom->vertexDataAsPoint2D();
    v[0].set(o.x() - 20, o.y());
    v[1].set(o.x() + 20, o.y());
    v[2].set(o.x(), o.y() - 20);
    v[3].set(o.x(), o.y() + 20);

    auto *node = new QSGGeometryNode();
    node->setGeometry(geom);
    node->setFlag(QSGNode::OwnsGeometry);

    auto *mat = new QSGFlatColorMaterial();
    mat->setColor(Qt::red);
    node->setMaterial(mat);
    node->setFlag(QSGNode::OwnsMaterial);

    root->appendChildNode(node);
}
