#ifndef DRILLDOCUMENTPREVIEWQUICKITEM_H
#define DRILLDOCUMENTPREVIEWQUICKITEM_H

#include <QObject>
#include <QQuickItem>
#include <QPointF>

#include "DrillDocumentModel.h"

class DrillDocument;

class DrillDocumentPreviewQuickItem : public QQuickItem
{
    Q_OBJECT
    QML_NAMED_ELEMENT(DrillDocumentPreview)

    Q_PROPERTY(DrillDocumentModel* model READ model WRITE setModel NOTIFY modelChanged)

    Q_PROPERTY(double gridStep READ gridStep WRITE setGridStep NOTIFY gridStepChanged)
    Q_PROPERTY(double zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(QPointF pan READ pan WRITE setPan NOTIFY panChanged)

public:
    explicit DrillDocumentPreviewQuickItem(QQuickItem* parent = nullptr);

    DrillDocumentModel* model() const { return documentModel_; }
    void setModel(DrillDocumentModel *newModel);

    double gridStep() const { return gridStep_; }
    void setGridStep(double s);
    double zoom() const { return zoom_; }
    void setZoom(double z);
    QPointF pan() const { return pan_; }
    void setPan(const QPointF& p);

private:
    int hitTest(const QPointF &px) const;
    double toolRadius(int toolId) const;
    QPointF toScreenDoc(const QPointF &mm) const;
    QPointF toScreenWorld(const QPointF &mm) const;
    QPointF toWorld(const QPointF &px) const;
    void buildBackground(QSGNode *root);
    void buildGrid(QSGNode *root);
    void buildOrigin(QSGNode *root);
    void buildDrills(QSGNode *root);

protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:
    void modelChanged();
    void gridStepChanged();
    void zoomChanged();
    void panChanged();

private:
    DrillDocumentModel *documentModel_ = nullptr;
    double gridStep_ = 1.0;
    double zoom_ = 20.0;
    QPointF pan_{0, 0};
    QPointF lastMousePos_;
    QPointF moveStartWorld_;
    QPointF moveStartOffset_;
    bool panning_ = false;
    bool movingDrills_ = false;
    static constexpr double GRID_MM = 10.0;
};

#endif // DRILLDOCUMENTPREVIEWQUICKITEM_H
