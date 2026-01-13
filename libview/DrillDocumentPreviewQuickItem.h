#ifndef DRILLDOCUMENTPREVIEWQUICKITEM_H
#define DRILLDOCUMENTPREVIEWQUICKITEM_H

#include <QObject>
#include <QQuickItem>
#include <QPointF>

#include "DrillDocument.h"

class DrillModel;

class DrillDocumentPreviewQuickItem : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(DrillDocument* document READ document WRITE setDocument NOTIFY documentChanged)
    Q_PROPERTY(double zoom READ zoom WRITE setZoom NOTIFY zoomChanged)
    Q_PROPERTY(QPointF pan READ pan WRITE setPan NOTIFY panChanged)

public:
    explicit DrillDocumentPreviewQuickItem(QQuickItem* parent = nullptr);

    DrillDocument* document() const { return doc_; }
    void setDocument(DrillDocument *newDoc);
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
    void documentChanged();
    void zoomChanged();
    void panChanged();

private:
    DrillDocument *doc_ = nullptr;
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
