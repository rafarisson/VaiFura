#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <cmath>
#include "DrillRendererHelper.h"
#include "DrillRendererBase.h"
#include "DrillDocument.h"
#include "DrillDocumentModel.h"
#include "ViewportTransform.h"

void DrillRendererBase::build(QSGNode *root,
                              const DrillDocumentModel *model,
                              const ViewportTransform &vp,
                              const QPointF &delta)
{
    DrillRendererHelper::forEachHole(model, delta,
                             [&](const DrillNode *holeNode, const Hole *, const QPointF &p, double r) {
                    QPointF screen = vp.toScreen(p);
                    root->appendChildNode(createCircleOutline(screen, r * vp.zoom(), 1.0, holeColor(holeNode)));
    });
}

QColor DrillRendererBase::holeColor(const DrillNode *holeNode) const
{
    return holeNode->isChecked() ? Qt::cyan : Qt::darkGray;
}

QSGGeometryNode *DrillRendererBase::createCircleOutline(const QPointF &center, double radiusPx, double thicknessPx, const QColor &color, int segments)
{
    const int verts = segments * 6;

    auto *geom = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(), verts);
    geom->setDrawingMode(QSGGeometry::DrawTriangles);

    auto *v = geom->vertexDataAsPoint2D();

    double rO = radiusPx + thicknessPx * 0.5;
    double rI = radiusPx - thicknessPx * 0.5;

    int idx = 0;
    for (int i = 0; i < segments; ++i) {
        double a0 = (i * 2.0 * M_PI) / segments;
        double a1 = ((i + 1) * 2.0 * M_PI) / segments;

        QPointF o0(center.x() + std::cos(a0) * rO,
                   center.y() + std::sin(a0) * rO);
        QPointF o1(center.x() + std::cos(a1) * rO,
                   center.y() + std::sin(a1) * rO);
        QPointF i0(center.x() + std::cos(a0) * rI,
                   center.y() + std::sin(a0) * rI);
        QPointF i1(center.x() + std::cos(a1) * rI,
                   center.y() + std::sin(a1) * rI);

        v[idx++].set(o0.x(), o0.y());
        v[idx++].set(i0.x(), i0.y());
        v[idx++].set(o1.x(), o1.y());

        v[idx++].set(o1.x(), o1.y());
        v[idx++].set(i0.x(), i0.y());
        v[idx++].set(i1.x(), i1.y());
    }

    auto *node = new QSGGeometryNode();
    node->setGeometry(geom);
    node->setFlag(QSGNode::OwnsGeometry);

    auto *mat = new QSGFlatColorMaterial();
    mat->setColor(color);
    node->setMaterial(mat);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}
