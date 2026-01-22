#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <cmath>
#include "GridRenderer.h"
#include "ViewportTransform.h"

void GridRenderer::build(QSGNode *root, const ViewportTransform &vp, double baseStep)
{
    double step = baseStep;
    double px = step * vp.zoom();

    while (px < 12.0) { step *= 2.0; px = step * vp.zoom(); }
    while (px > 80.0) { step *= 0.5; px = step * vp.zoom(); }

    QRectF wr = vp.visibleWorldRect();
    double margin = step * 10;

    wr.adjust(-margin, -margin, margin, margin);

    int ix0 = int(std::floor(wr.left()   / step));
    int ix1 = int(std::ceil (wr.right()  / step));
    int iy0 = int(std::floor(wr.top()    / step));
    int iy1 = int(std::ceil (wr.bottom() / step));

    int maxLines = (ix1 - ix0 + iy1 - iy0 + 2) * 2;

    auto *geom = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(),
        maxLines * 2
        );
    geom->setDrawingMode(QSGGeometry::DrawLines);

    auto *v = geom->vertexDataAsPoint2D();
    int idx = 0;

    for (int i = ix0; i <= ix1; ++i) {
        QPointF a = vp.toScreen({i * step, wr.top()});
        QPointF b = vp.toScreen({i * step, wr.bottom()});
        a.rx() = std::round(a.x()) + 0.5;
        b.rx() = std::round(b.x()) + 0.5;
        v[idx++].set(a.x(), a.y());
        v[idx++].set(b.x(), b.y());
    }

    for (int i = iy0; i <= iy1; ++i) {
        QPointF a = vp.toScreen({wr.left(), i * step});
        QPointF b = vp.toScreen({wr.right(), i * step});
        a.ry() = std::round(a.y()) + 0.5;
        b.ry() = std::round(b.y()) + 0.5;
        v[idx++].set(a.x(), a.y());
        v[idx++].set(b.x(), b.y());
    }

    geom->allocate(idx);

    auto *node = new QSGGeometryNode();
    node->setGeometry(geom);
    node->setFlag(QSGNode::OwnsGeometry);

    auto *mat = new QSGFlatColorMaterial();
    mat->setColor(QColor(0x2a2a2a));
    node->setMaterial(mat);
    node->setFlag(QSGNode::OwnsMaterial);

    root->appendChildNode(node);
}
