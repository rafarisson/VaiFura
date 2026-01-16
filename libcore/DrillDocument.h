#ifndef DRILLDOCUMENT_H
#define DRILLDOCUMENT_H

#include <QVector>
#include "DrillNode.h"

struct Tool
{
    int id = -1;
    double mm = 0;
};

struct Hole {
    double x = 0;
    double y = 0;
    int toolId = -1;
};

class DrillDocument
{
public:
    DrillDocument() = default;
    DrillDocument(const DrillDocument&) = delete;
    DrillDocument& operator=(const DrillDocument&) = delete;

    const QVector<Tool>& tools() const { return tools_; }
    const QVector<Hole>& holes() const { return holes_; }

    DrillNode* root() { return &root_; }
    const DrillNode* root() const { return &root_; }

    void clear();

private:
    friend class DrillDocumentBuilder;

    QVector<Tool> tools_;
    QVector<Hole> holes_;
    DrillNode root_{DrillNode::Type::IsTool};
};

#endif // DRILLDOCUMENT_H
