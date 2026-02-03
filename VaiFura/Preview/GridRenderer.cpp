#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <cmath>
#include "GridRenderer.h"
#include "ViewportTransform.h"

void GridRenderer::build(QSGNode *root, const ViewportTransform &vp, double baseStep)
{
    double step = baseStep;

    if (step <= 0.0 || vp.zoom() <= 0.0)
        return;

    QRectF wr = vp.visibleWorldRect();

    int ix0 = int(std::floor(wr.left()   / step));
    int ix1 = int(std::ceil (wr.right()  / step));
    int iy0 = int(std::floor(wr.top()    / step));
    int iy1 = int(std::ceil (wr.bottom() / step));

    if (ix0 > ix1 || iy0 > iy1)
        return;

    int numV = ix1 - ix0 + 1;
    int numH = iy1 - iy0 + 1;

    int maxLines = numV + numH;

    auto *geom = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(),
        maxLines * 2
        );
    geom->setDrawingMode(QSGGeometry::DrawLines);

    auto *v = geom->vertexDataAsPoint2D();
    int idx = 0;

    QPointF o = vp.toScreen({0, 0});
    double snapX = std::round(o.x()) - o.x();
    double snapY = std::round(o.y()) - o.y();

    for (int i = ix0; i <= ix1; ++i) {
        QPointF a = vp.toScreen({i * step, wr.top()});
        QPointF b = vp.toScreen({i * step, wr.bottom()});

        a.rx() += snapX;
        b.rx() += snapX;

        v[idx++].set(a.x(), a.y());
        v[idx++].set(b.x(), b.y());
    }

    for (int i = iy0; i <= iy1; ++i) {
        QPointF a = vp.toScreen({wr.left(),  i * step});
        QPointF b = vp.toScreen({wr.right(), i * step});

        a.ry() += snapY;
        b.ry() += snapY;

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
