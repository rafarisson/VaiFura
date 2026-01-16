#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QMouseEvent>

#include "DrillDocumentPreviewQuickItem.h"
#include "DrillDocument.h"

static QSGGeometryNode *createQuad(const QRectF &r, const QColor &color);
static QSGGeometryNode *createCircleOutline(const QPointF &center,
                                            double radiusPx, double thicknessPx,
                                            const QColor &color,
                                            int segments = 32);
static double snap(double v, double step);
static QPointF snapPoint(const QPointF &p, double step);

DrillDocumentPreviewQuickItem::DrillDocumentPreviewQuickItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);
}

void DrillDocumentPreviewQuickItem::setModel(DrillDocumentModel *newModel)
{
    if (documentModel_ == newModel)
        return;

    if (documentModel_)
        disconnect(documentModel_, nullptr, this, nullptr);
    documentModel_ = newModel;
    if (documentModel_)
        connect(documentModel_, &DrillDocumentModel::changed, this, &DrillDocumentPreviewQuickItem::update);

    emit modelChanged();
    update();
}

void DrillDocumentPreviewQuickItem::setGridStep(double s)
{
    if (qFuzzyCompare(gridStep_, s))
        return;

    gridStep_ = s;
    emit gridStepChanged();
    update();
}

void DrillDocumentPreviewQuickItem::setZoom(double z)
{
    z = std::clamp(z, 1.0, 500.0);
    if (zoom_ == z)
        return;
    zoom_ = z;
    emit zoomChanged();
    update();
}

void DrillDocumentPreviewQuickItem::setPan(const QPointF &p)
{
    if (pan_ == p)
        return;
    pan_ = p;
    emit panChanged();
    update();
}

QSGNode *DrillDocumentPreviewQuickItem::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    QSGNode* root = oldNode;
    if (!root)
        root = new QSGNode();

    root->removeAllChildNodes();

    auto *clipNode = new QSGClipNode();
    clipNode->setIsRectangular(true);
    clipNode->setClipRect(boundingRect());

    root->appendChildNode(clipNode);

    buildBackground(clipNode);
    buildGrid(clipNode);
    buildOrigin(clipNode);

    if (documentModel_ && documentModel_->document())
        buildDrills(clipNode);

    return root;
}

void DrillDocumentPreviewQuickItem::mousePressEvent(QMouseEvent *event)
{
    lastMousePos_ = event->position();

    if (event->button() == Qt::LeftButton) {
        panning_ = true;
        return;
    }

    if (event->button() == Qt::RightButton && documentModel_) {
        movingDrills_ = true;
        moveStartWorld_ = toWorld(event->position());
        moveStartOffset_ = documentModel_->offset();
        return;
    }

    // int hit = hitTest(event->position());
    // if (hit >= 0) {
    //     setSelectedDrill(hit);
    //     emit drillClicked(hit);
    // }
}

void DrillDocumentPreviewQuickItem::mouseMoveEvent(QMouseEvent *event)
{
    if (panning_) {
        QPointF deltaPx = event->position() - lastMousePos_;

        lastMousePos_ = event->position();
        pan_.rx() += deltaPx.x() / zoom_;
        pan_.ry() -= deltaPx.y() / zoom_;

        update();
        return;
    }

    if (movingDrills_ && documentModel_) {
        QPointF currentWorld = toWorld(event->position());
        QPointF deltaWorld = currentWorld - moveStartWorld_;

        QPointF candidate = moveStartOffset_ + deltaWorld;

        snapPreviewWorld_ = snapPoint(candidate, gridStep_);
        snapPreviewActive_ = true;

        update();
        return;
    }
}

void DrillDocumentPreviewQuickItem::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        panning_ = false;
        pan_ = snapPoint(pan_, gridStep_);
        update();
    }

    if (event->button() == Qt::RightButton)
        movingDrills_ = false;
}

void DrillDocumentPreviewQuickItem::wheelEvent(QWheelEvent *event)
{
    setZoom(zoom_ * (event->angleDelta().y() > 0 ? 1.1 : 0.9));
}

int DrillDocumentPreviewQuickItem::hitTest(const QPointF &px) const
{
    if (!documentModel_ || !documentModel_->document())
        return -1;

    auto *m = documentModel_->document();

    for (int i = 0; i < m->holes().size(); ++i) {
        QPointF c = toScreenDoc({m->holes()[i].x, m->holes()[i].y});
        if (QLineF(px, c).length() < toolRadius(m->holes()[i].toolId) * zoom_)
            return i;
    }

    return -1;
}

double DrillDocumentPreviewQuickItem::toolRadius(int toolId) const
{
    if (documentModel_ && documentModel_->document()) {
        auto *m = documentModel_->document();
        for (const auto& t : m->tools())
            if (t.id == toolId)
                return t.mm * 0.5;
    }

    return 0.2;
}

QPointF DrillDocumentPreviewQuickItem::toScreenDoc(const QPointF &mm) const
{
    QPointF world = mm;

    world += documentModel_->offset();

    return toScreenWorld(world);
}

QPointF DrillDocumentPreviewQuickItem::toScreenWorld(const QPointF &mm) const
{
    return {
        width() * 0.5 + (mm.x() + pan_.x()) * zoom_,
        height() * 0.5 - (mm.y() + pan_.y()) * zoom_
    };
}

QPointF DrillDocumentPreviewQuickItem::toWorld(const QPointF &px) const
{
    return {
        (px.x() - width() * 0.5) / zoom_ - pan_.x(),
        -(px.y() - height() * 0.5) / zoom_ - pan_.y()
    };
}

void DrillDocumentPreviewQuickItem::buildBackground(QSGNode *root)
{
    root->appendChildNode(createQuad({0, 0, width(), height()}, QColor(0x1e1e1e)));
}

void DrillDocumentPreviewQuickItem::buildGrid(QSGNode *root)
{
    // --- resolve unidade ---
    double unitScale = 1.0;
    double minorStep = gridStep_;
    double majorStep = gridStep_ * 10.0;

    // --- limites visíveis em coordenadas de mundo ---
    QPointF w1 = toWorld({0, 0});
    QPointF w2 = toWorld({width(), height()});

    double worldMinX = std::min(w1.x(), w2.x());
    double worldMaxX = std::max(w1.x(), w2.x());
    double worldMinY = std::min(w1.y(), w2.y());
    double worldMaxY = std::max(w1.y(), w2.y());

    // margem para estabilidade do pan
    double margin = majorStep * 2;
    worldMinX -= margin;
    worldMaxX += margin;
    worldMinY -= margin;
    worldMaxY += margin;

    // --- quantização ---
    double minX = std::floor(worldMinX / minorStep) * minorStep;
    double maxX = std::ceil (worldMaxX / minorStep) * minorStep;
    double minY = std::floor(worldMinY / minorStep) * minorStep;
    double maxY = std::ceil (worldMaxY / minorStep) * minorStep;

    // --- contagem de linhas ---
    int minorV = int((maxX - minX) / minorStep) + 1;
    int minorH = int((maxY - minY) / minorStep) + 1;

    int majorV = int((maxX - minX) / majorStep) + 1;
    int majorH = int((maxY - minY) / majorStep) + 1;

    // --- NODES ---
    auto *minorGeom = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(),
        (minorV + minorH) * 2
        );
    minorGeom->setDrawingMode(QSGGeometry::DrawLines);

    auto *majorGeom = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(),
        (majorV + majorH) * 2
        );
    majorGeom->setDrawingMode(QSGGeometry::DrawLines);

    auto *vMinor = minorGeom->vertexDataAsPoint2D();
    auto *vMajor = majorGeom->vertexDataAsPoint2D();

    int im = 0;
    int iM = 0;

    // --- linhas verticais ---
    for (double x = minX; x <= maxX + 1e-9; x += minorStep) {
        QPointF a = toScreenWorld({x, minY});
        QPointF b = toScreenWorld({x, maxY});

        if (std::fmod(std::abs(x), majorStep) < 1e-6) {
            vMajor[iM++].set(a.x(), a.y());
            vMajor[iM++].set(b.x(), b.y());
        } else {
            vMinor[im++].set(a.x(), a.y());
            vMinor[im++].set(b.x(), b.y());
        }
    }

    // --- linhas horizontais ---
    for (double y = minY; y <= maxY + 1e-9; y += minorStep) {
        QPointF a = toScreenWorld({minX, y});
        QPointF b = toScreenWorld({maxX, y});

        if (std::fmod(std::abs(y), majorStep) < 1e-6) {
            vMajor[iM++].set(a.x(), a.y());
            vMajor[iM++].set(b.x(), b.y());
        } else {
            vMinor[im++].set(a.x(), a.y());
            vMinor[im++].set(b.x(), b.y());
        }
    }

    minorGeom->allocate(im);
    majorGeom->allocate(iM);

    // --- minor grid node ---
    auto *minorNode = new QSGGeometryNode();
    minorNode->setGeometry(minorGeom);
    minorNode->setFlag(QSGNode::OwnsGeometry);

    auto *minorMat = new QSGFlatColorMaterial();
    minorMat->setColor(QColor(0x2a2a2a));
    minorNode->setMaterial(minorMat);
    minorNode->setFlag(QSGNode::OwnsMaterial);

    // --- major grid node ---
    auto *majorNode = new QSGGeometryNode();
    majorNode->setGeometry(majorGeom);
    majorNode->setFlag(QSGNode::OwnsGeometry);

    auto *majorMat = new QSGFlatColorMaterial();
    majorMat->setColor(QColor(0x3a3a3a));
    majorNode->setMaterial(majorMat);
    majorNode->setFlag(QSGNode::OwnsMaterial);

    // --- eixos ---
    auto *axisGeom = new QSGGeometry(
        QSGGeometry::defaultAttributes_Point2D(), 4);
    axisGeom->setDrawingMode(QSGGeometry::DrawLines);

    auto *va = axisGeom->vertexDataAsPoint2D();
    QPointF ox = toScreenWorld({0, 0});

    va[0].set(ox.x(), 0);
    va[1].set(ox.x(), height());
    va[2].set(0, ox.y());
    va[3].set(width(), ox.y());

    auto *axisNode = new QSGGeometryNode();
    axisNode->setGeometry(axisGeom);
    axisNode->setFlag(QSGNode::OwnsGeometry);

    auto *axisMat = new QSGFlatColorMaterial();
    axisMat->setColor(QColor(0x804040));
    axisNode->setMaterial(axisMat);
    axisNode->setFlag(QSGNode::OwnsMaterial);

    // --- ordem correta ---
    root->appendChildNode(minorNode);
    root->appendChildNode(majorNode);
    root->appendChildNode(axisNode);
}

void DrillDocumentPreviewQuickItem::buildOrigin(QSGNode *root)
{
    auto *geom = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    geom->setDrawingMode(QSGGeometry::DrawLines);

    auto *v = geom->vertexDataAsPoint2D();
    QPointF o = toScreenWorld({0, 0});

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

void DrillDocumentPreviewQuickItem::buildDrills(QSGNode *root)
{
    if (!documentModel_ || !documentModel_->document())
        return;

    auto *m = documentModel_->document();

    for (int i = 0; i < m->holes().size(); ++i) {
        const auto &d = m->holes()[i];
        QPointF c = toScreenDoc({d.x, d.y});
        double r = toolRadius(d.toolId) * zoom_;

        root->appendChildNode(
            createCircleOutline(
                c,
                r,
                1.0,
                Qt::cyan
                )
            );
    }
}

static QSGGeometryNode *createQuad(const QRectF &r, const QColor &color)
{
    auto* geom = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 6);
    geom->setDrawingMode(QSGGeometry::DrawTriangles);

    auto* v = geom->vertexDataAsPoint2D();
    v[0].set(r.left(),  r.top());
    v[1].set(r.right(), r.top());
    v[2].set(r.right(), r.bottom());
    v[3].set(r.left(),  r.top());
    v[4].set(r.right(), r.bottom());
    v[5].set(r.left(),  r.bottom());

    auto* node = new QSGGeometryNode();
    node->setGeometry(geom);
    node->setFlag(QSGNode::OwnsGeometry);

    auto* mat = new QSGFlatColorMaterial();
    mat->setColor(color);
    node->setMaterial(mat);
    node->setFlag(QSGNode::OwnsMaterial);

    return node;
}

static QSGGeometryNode *createCircleOutline(const QPointF &center,
                                            double radiusPx, double thicknessPx,
                                            const QColor &color,
                                            int segments)
{
    const int verts = segments * 6;

    auto *geom = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), verts);
    geom->setDrawingMode(QSGGeometry::DrawTriangles);

    auto *v = geom->vertexDataAsPoint2D();

    double rOuter = radiusPx + thicknessPx * 0.5;
    double rInner = radiusPx - thicknessPx * 0.5;

    int idx = 0;
    for (int i = 0; i < segments; ++i) {
        double a0 = (i * 2.0 * M_PI) / segments;
        double a1 = ((i + 1) * 2.0 * M_PI) / segments;

        QPointF o0(center.x() + std::cos(a0) * rOuter,
                   center.y() + std::sin(a0) * rOuter);
        QPointF o1(center.x() + std::cos(a1) * rOuter,
                   center.y() + std::sin(a1) * rOuter);

        QPointF i0(center.x() + std::cos(a0) * rInner,
                   center.y() + std::sin(a0) * rInner);
        QPointF i1(center.x() + std::cos(a1) * rInner,
                   center.y() + std::sin(a1) * rInner);

        // triângulo 1
        v[idx++].set(o0.x(), o0.y());
        v[idx++].set(i0.x(), i0.y());
        v[idx++].set(o1.x(), o1.y());

        // triângulo 2
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

static double snap(double v, double step)
{
    return std::round(v / step) * step;
}

static QPointF snapPoint(const QPointF &p, double step)
{
    return {
        snap(p.x(), step),
        snap(p.y(), step)
    };
}
