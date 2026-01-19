#ifndef ORIGINRENDERER_H
#define ORIGINRENDERER_H

#include <QSGNode>

class ViewportTransform;

class OriginRenderer
{
public:
    void build(QSGNode *root, const ViewportTransform &vp);
};

#endif // ORIGINRENDERER_H
