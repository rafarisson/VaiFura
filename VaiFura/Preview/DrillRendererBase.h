#ifndef DRILLRENDERERBASE_H
#define DRILLRENDERERBASE_H

#include <QSGNode>

class DrillDocumentModel;
class ViewportTransform;
class DrillNode;

class DrillRendererBase
{
public:
    explicit DrillRendererBase() = default;
    virtual ~DrillRendererBase() = default;

    void build(QSGNode *root,
               const DrillDocumentModel *model,
               const ViewportTransform &vp,
               const QPointF &delta = {0, 0});

protected:
    virtual QColor holeColor(const DrillNode *holeNode) const;

private:
    QSGGeometryNode *createCircleOutline(const QPointF &center,
                                         double radiusPx,
                                         double thicknessPx,
                                         const QColor &color,
                                         int segments = 32);
};

#endif // DRILLRENDERERBASE_H
