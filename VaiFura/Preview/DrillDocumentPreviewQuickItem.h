#ifndef DRILLDOCUMENTPREVIEWQUICKITEM_H
#define DRILLDOCUMENTPREVIEWQUICKITEM_H

#include <QObject>
#include <QQuickItem>
#include <QPointF>

#include "DrillDocumentModel.h"
#include "InteractionController.h"
#include "SnapEngine.h"
#include "SnapPreviewRenderer.h"
#include "ViewportTransform.h"
#include "GridRenderer.h"
#include "OriginRenderer.h"
#include "DrillRenderer.h"

class DrillDocumentModel;

class DrillDocumentPreviewQuickItem : public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DrillDocumentPreview)

    Q_PROPERTY(DrillDocumentModel* model READ model WRITE setModel NOTIFY modelChanged)

public:
    explicit DrillDocumentPreviewQuickItem(QQuickItem *parent = nullptr);

    DrillDocumentModel* model() const { return documentModel_; }
    void setModel(DrillDocumentModel *newModel);

    Q_INVOKABLE void fitToContent(double marginPx = 40.0);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void buildBackground(QSGNode *root);

signals:
    void modelChanged();

private:
    DrillDocumentModel *documentModel_ = nullptr;

    ViewportTransform viewport_;
    SnapEngine snap_;
    InteractionController interaction_;

    GridRenderer grid_;
    OriginRenderer origin_;
    DrillRenderer drill_;

    bool snapPreviewActive_ = false;
    QPointF snapDeltaWorld_;
    SnapPreviewRenderer snapPreview_;
};

#endif // DRILLDOCUMENTPREVIEWQUICKITEM_H
