#include <QColor>
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include <QSGFlatColorMaterial>
#include "OptimizationRenderer.h"
#include "DrillTransformModel.h"
#include "OptimizationModel.h"
#include "ViewportTransform.h"

void OptimizationRenderer::setShowPath(bool enabled)
{
    showPath_ = enabled;
}

void OptimizationRenderer::setShowOrder(bool enabled)
{
    showOrder_ = enabled;
}

void OptimizationRenderer::build(QSGNode *root,
                                 const OptimizationModel *model,
                                 const DrillTransformModel *transform,
                                 const ViewportTransform &vp,
                                 const QColor &color,
                                 QQuickWindow *window)
{
    if (!root || !model || !model->currentPlan())
        return;
    if (!showPath_ && !showOrder_)
        return;

    const auto &holes = model->currentPlan()->holes();
    const auto &order = model->currentPlan()->order();

    for (int i = 1; i < order.size(); ++i) {
        QPointF a = holes[order[i - 1]].pos;
        QPointF b = holes[order[i]].pos;

        if (transform) {
            a = transform->transform()->apply(a);
            b = transform->transform()->apply(b);
        }

        a = vp.toScreen(a);
        b = vp.toScreen(b);

        if (showPath_)
            root->appendChildNode(createLine(a, b, color, 1.5f));

        if (showOrder_) {
            root->appendChildNode(createText(a, QString::number(i), color, window));
            if (i == order.size() - 1)
                root->appendChildNode(createText(b, QString::number(i + 1), color, window));
        }
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

QSGSimpleTextureNode *OptimizationRenderer::createText(const QPointF &pos, const QString &text, const QColor &color, QQuickWindow *window)
{
    QFont font;
    font.setPointSize(10);

    QFontMetrics fm(font);
    QSize size = fm.size(Qt::TextSingleLine, text);

    QImage image(size, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setFont(font);
    // Sombra
    painter.setPen(Qt::black);
    painter.drawText(1, fm.ascent() + 1, text);
    // Texto
    painter.setPen(color);
    painter.drawText(0, fm.ascent(), text);
    painter.end();

    auto *texture = window->createTextureFromImage(image);

    auto *node = new QSGSimpleTextureNode();
    node->setTexture(texture);
    node->setRect(pos.x(), pos.y(), size.width(), size.height());

    return node;
}
