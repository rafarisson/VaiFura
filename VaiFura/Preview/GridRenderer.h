#ifndef GRIDRENDERER_H
#define GRIDRENDERER_H

#include <QSGNode>

class ViewportTransform;

class GridRenderer
{
public:
    void build(QSGNode *root, const ViewportTransform &vp, double baseStep);
};

#endif // GRIDRENDERER_H
