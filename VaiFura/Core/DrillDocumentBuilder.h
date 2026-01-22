#ifndef DRILLDOCUMENTBUILDER_H
#define DRILLDOCUMENTBUILDER_H

#include "DrillDocument.h"

class DrillDocumentBuilder
{
public:
    explicit DrillDocumentBuilder(DrillDocument *document);

    void addTool(const Tool &tool);
    void addHole(const Hole &hole);
    void clear();

    void build();

private:
    DrillNode *createToolNode(DrillNode *parent, const Tool &tool);
    void appendHoleNodes(DrillNode *toolNode, const Tool &tool, const QVector<Hole> &holes);

private:
    DrillDocument *doc_;
};

#endif // DRILLDOCUMENTBUILDER_H
