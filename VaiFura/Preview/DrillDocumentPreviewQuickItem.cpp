#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QMouseEvent>
#include "BoardProfile.h"
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
        connect(documentModel_, &DrillDocumentModel::profileChanged, this, &DrillDocumentPreviewQuickItem::update);
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
        connect(transformModel_, &DrillTransformModel::transformChanged, this, &DrillDocumentPreviewQuickItem::onTransformChanged);

    emit transformModelChanged();
    update();
}

void DrillDocumentPreviewQuickItem::setOptimizationModel(OptimizationModel *newModel)
{
    if (optimizationModel_ == newModel)
        return;

    if (optimizationModel_)
        disconnect(optimizationModel_, nullptr, this, nullptr);

    optimizationModel_ = newModel;

    if (optimizationModel_)
        connect(optimizationModel_, &OptimizationModel::optimizationPlanChanged, this, &DrillDocumentPreviewQuickItem::update);

    emit optimizationModelChanged();
    update();
}

void DrillDocumentPreviewQuickItem::fitToContent(double marginPx)
{
    if (!documentModel_)
        return;

    QRectF contentBounds;
    bool first = true;

    auto includeRect = [&](const QRectF& r) {
        if (first) {
            contentBounds = r;
            first = false;
        } else {
            contentBounds |= r;
        }
    };

    if (documentModel_->document()) {
        DrillRendererHelper::forEachHole(documentModel_, transformModel_, {},
                                         [&](auto, auto, const QPointF &p, double radius)
                                         {
                                             QRectF hr(p.x() - radius, p.y() - radius, radius * 2, radius * 2);
                                             includeRect(hr);
                                         });
    }

    if (auto profile = documentModel_->profile()) {
        for (const BoardPath& path : profile->paths()) {
            for (const BoardPoint& pt : path.points) {

                QPointF p(pt.x, pt.y);

                if (transformModel_ && transformModel_->transform())
                    p = transformModel_->transform()->apply(p);

                QRectF pr(p.x(), p.y(), 0.001, 0.001);
                includeRect(pr);
            }
        }
    }

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
    origin_.build(clipNode, transformModel_, viewport_);

    if (documentModel_) {
        if (documentModel_->document()) {
            QColor color(Qt::cyan);
            drill_.build(clipNode, documentModel_, transformModel_, viewport_, color);
            if (interaction_.snapActive()) {
                color.setAlpha(128);
                drill_.build(clipNode, documentModel_, transformModel_, viewport_, color, interaction_.snapDelta());
            }
        }

        if (documentModel_->profile()) {
            QColor color(Qt::yellow);
            profile_.build(clipNode, documentModel_->profile(), transformModel_, viewport_, color);
            if (interaction_.snapActive()) {
                color.setAlpha(128);
                profile_.build(clipNode, documentModel_->profile(), transformModel_, viewport_, color, interaction_.snapDelta());
            }
        }

        if (!interaction_.snapActive())
            optimization_.build(clipNode, optimizationModel_, transformModel_, viewport_, QColor(202, 119, 20));
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

void DrillDocumentPreviewQuickItem::onTransformChanged()
{
    interaction_.initSnap();
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

