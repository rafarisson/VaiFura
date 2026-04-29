#ifndef DRILLDOCUMENTPREVIEWQUICKITEM_H
#define DRILLDOCUMENTPREVIEWQUICKITEM_H

#include <QObject>
#include <QQuickItem>
#include <QPointF>

#include "DrillDocumentModel.h"
#include "DrillTransformModel.h"
#include "OptimizationModel.h"
#include "InteractionController.h"
#include "SnapEngine.h"
#include "ViewportTransform.h"
#include "GridRenderer.h"
#include "OriginRenderer.h"
#include "DrillRenderer.h"
#include "ProfileRenderer.h"
#include "OptimizationRenderer.h"

class DrillDocumentPreviewQuickItem : public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DrillDocumentPreview)

    Q_PROPERTY(DrillDocumentModel* model READ model WRITE setModel NOTIFY modelChanged FINAL)
    Q_PROPERTY(DrillTransformModel* transformModel READ transformModel WRITE setTransformModel NOTIFY transformModelChanged FINAL)
    Q_PROPERTY(OptimizationModel* optimizationModel READ optimizationModel WRITE setOptimizationModel NOTIFY optimizationModelChanged FINAL)
    Q_PROPERTY(bool showOptimizationPath READ showOptimizationPath WRITE setShowOptimizationPath NOTIFY showOptimizationPathChanged FINAL)
    Q_PROPERTY(bool showOptimizationOrder READ showOptimizationOrder WRITE setShowOptimizationOrder NOTIFY showOptimizationOrderChanged FINAL)

public:
    explicit DrillDocumentPreviewQuickItem(QQuickItem *parent = nullptr);

    DrillDocumentModel* model() const { return documentModel_; }
    void setModel(DrillDocumentModel *newModel);

    DrillTransformModel* transformModel() const { return transformModel_; }
    void setTransformModel(DrillTransformModel *newModel);

    OptimizationModel* optimizationModel() const { return optimizationModel_; }
    void setOptimizationModel(OptimizationModel *newModel);

    bool showOptimizationPath() const { return optimizationRenderer_.showPath(); }
    void setShowOptimizationPath(bool enabled);

    bool showOptimizationOrder() const { return optimizationRenderer_.showOrder(); }
    void setShowOptimizationOrder(bool enabled);

    Q_INVOKABLE void fitToContent(double marginPx = 40.0);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void onTransformChanged();

private:
    void buildBackground(QSGNode *root);

signals:
    void modelChanged();
    void showOptimizationPathChanged();
    void showOptimizationOrderChanged();
    void transformModelChanged();
    void optimizationModelChanged();

private:
    DrillDocumentModel *documentModel_ = nullptr;
    DrillTransformModel *transformModel_ = nullptr;
    OptimizationModel *optimizationModel_ = nullptr;

    ViewportTransform viewport_;
    SnapEngine snap_;
    InteractionController interaction_;

    GridRenderer gridRenderer_;
    OriginRenderer originRenderer_;
    DrillRenderer drillRenderer_;
    ProfileRenderer profileRenderer_;
    OptimizationRenderer optimizationRenderer_;

    bool snapPreviewActive_ = false;
    QPointF snapDeltaWorld_;
};

#endif // DRILLDOCUMENTPREVIEWQUICKITEM_H
