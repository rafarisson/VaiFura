#ifndef DRILLTREEDOCUMENTBUILDER_H
#define DRILLTREEDOCUMENTBUILDER_H

#include "DrillDocument.h"

class DrillTreeNode;
class DrillTreeDocument;

class DrillTreeDocumentBuilder
{
public:
    void build(DrillTreeDocument &dst, const DrillDocument &document);

private:
    DrillTreeNode *createToolNode(DrillTreeNode *parent, const Tool &tool);
    void appendHoleNodes(DrillTreeNode *toolNode, const Tool &tool, const DrillDocument &doc);
};

#endif // DRILLTREEDOCUMENTBUILDER_H
