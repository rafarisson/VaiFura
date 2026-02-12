#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QMouseEvent>
#include "DrillRendererHelper.h"
#include "DrillDocumentPreviewQuickItem.h"

DrillDocumentPreviewQuickItem::DrillDocumentPreviewQuickItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
    setAcceptedMouseButtons(Qt::AllButtons);

    interaction_.setViewport(&viewport_);
    interaction_.setSnap(&snap_);
}

void DrillDocumentPreviewQuickItem::setModel(DrillDocumentModel *newModel)
{
    if (documentModel_ == newModel)
        return;

    if (documentModel_)
        disconnect(documentModel_, nullptr, this, nullptr);

    documentModel_ = newModel;

    if (documentModel_) {
        connect(documentModel_, &DrillDocumentModel::documentContentChanged, this, &DrillDocumentPreviewQuickItem::update);
        connect(documentModel_, &DrillDocumentModel::drillCheckeStateChanged, this, &DrillDocumentPreviewQuickItem::update);
    }

    emit modelChanged();
    update();
}

void DrillDocumentPreviewQuickItem::setTransformModel(DrillTransformModel *newModel)
{
    if (transformModel_ == newModel)
        return;

    if (transformModel_)
        disconnect(transformModel_, nullptr, this, nullptr);

    transformModel_ = newModel;
    interaction_.setTransformModel(transformModel_);

    if (transformModel_)
        connect(transformModel_, &DrillTransformModel::offsetChanged, this, &DrillDocumentPreviewQuickItem::update);

    emit transformModelChanged();
    update();
}

void DrillDocumentPreviewQuickItem::fitToContent(double marginPx)
{
    if (!documentModel_ || !documentModel_->document())
        return;

    QRectF contentBounds;
    bool first = true;

    DrillRendererHelper::forEachHole(documentModel_, transformModel_, {},
                             [&](auto, auto, const QPointF &p, double radius) {
                                 QRectF hr(p.x() - radius, p.y() - radius, radius * 2, radius * 2);
                                 if (first) {
                                     contentBounds = hr;
                                     first = false;
                                 } else {
                                     contentBounds |= hr;
                                 }
                             });

    if (first)
        return;

    viewport_.fitWorldRect(contentBounds, marginPx);
    update();
}

QSGNode *DrillDocumentPreviewQuickItem::updatePaintNode(QSGNode *old, UpdatePaintNodeData *)
{
    auto *root = old ? old : new QSGNode();
    root->removeAllChildNodes();

    auto *clipNode = new QSGClipNode();
    clipNode->setIsRectangular(true);
    clipNode->setClipRect(boundingRect());

    root->appendChildNode(clipNode);

    viewport_.setViewportSize({width(), height()});

    buildBackground(clipNode);

    grid_.build(clipNode, viewport_, 1.0);
    origin_.build(clipNode, viewport_);

    if (documentModel_ && documentModel_->document()) {
        drill_.build(clipNode, documentModel_, transformModel_, viewport_);
        if (interaction_.snapActive())
            snapPreview_.build(clipNode, documentModel_, transformModel_, viewport_, interaction_.snapDelta());
    }

    return root;
}

void DrillDocumentPreviewQuickItem::mousePressEvent(QMouseEvent *e)
{
    interaction_.mousePress(e->position(), e->button());
    update();
}

void DrillDocumentPreviewQuickItem::mouseMoveEvent(QMouseEvent *e)
{
    interaction_.mouseMove(e->position());
    update();
}

void DrillDocumentPreviewQuickItem::mouseReleaseEvent(QMouseEvent *e)
{
    interaction_.mouseRelease(e->position(), e->button());
    update();
}

void DrillDocumentPreviewQuickItem::wheelEvent(QWheelEvent *e)
{
    interaction_.wheel(e->angleDelta().y());
    update();
}

void DrillDocumentPreviewQuickItem::buildBackground(QSGNode *root)
{
    const QRectF r = boundingRect();

    auto *geom = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);
    geom->setDrawingMode(QSGGeometry::DrawTriangleStrip);

    auto *v = geom->vertexDataAsPoint2D();
    v[0].set(r.left(),  r.top());
    v[1].set(r.right(), r.top());
    v[2].set(r.left(),  r.bottom());
    v[3].set(r.right(), r.bottom());

    auto *node = new QSGGeometryNode();
    node->setGeometry(geom);
    node->setFlag(QSGNode::OwnsGeometry);

    auto *mat = new QSGFlatColorMaterial();
    mat->setColor(QColor(0x1e1e1e));
    node->setMaterial(mat);
    node->setFlag(QSGNode::OwnsMaterial);

    root->appendChildNode(node);
}

