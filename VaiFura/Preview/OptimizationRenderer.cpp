#include <QColor>
#include <QSGFlatColorMaterial>
#include "OptimizationRenderer.h"
#include "DrillTransformModel.h"
#include "OptimizationModel.h"
#include "ViewportTransform.h"

void OptimizationRenderer::build(QSGNode *root,
                                 const OptimizationModel *model,
                                 const DrillTransformModel *transform,
                                 const ViewportTransform &vp,
                                 const QColor &color)
{
    if (!root || !model || !model->optimizationPlan())
        return;

    const auto &holes = model->optimizationPlan()->holes();
    const auto &order = model->optimizationPlan()->order();

    for (int i = 1; i < order.size(); ++i) {
        QPointF a = holes[order[i - 1]].pos;
        QPointF b = holes[order[i]].pos;

        if (transform) {
            a = transform->transform()->apply(a);
            b = transform->transform()->apply(b);
        }

        a = vp.toScreen(a);
        b = vp.toScreen(b);

        root->appendChildNode(
            createLine(a, b, color, 1.5f)
            );
    }
}

QSGGeometryNode *OptimizationRenderer::createLine(const QPointF &a, const QPointF &b, const QColor &color, float thickness)
{
    auto* geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setDrawingMode(QSGGeometry::DrawLines);
    geometry->setLineWidth(thickness);

    auto* v = geometry->vertexDataAsPoint2D();
    v[0].set(a.x(), a.y());
    v[1].set(b.x(), b.y());

    auto* node = new QSGGeometryNode();
    node->setGeometry(geometry);
    node->setFlag(QSGNode::OwnsGeometry);

    auto* material = new QSGFlatColorMaterial();
    material->setColor(color);

    node->setMaterial(material);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}
