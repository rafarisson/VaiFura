#include "DrillTreeDocumentBuilder.h"
#include "DrillTreeDocument.h"
#include "DrillTreeNode.h"

void DrillTreeDocumentBuilder::build(DrillTreeDocument &dst, const DrillDocument& document)
{
    dst.reset();

    for (const Tool &tool : document.tools()) {
        DrillTreeNode *toolNode = createToolNode(dst.root(), tool);
        appendHoleNodes(toolNode, tool, document);
    }
}

DrillTreeNode *DrillTreeDocumentBuilder::createToolNode(DrillTreeNode *parent, const Tool &tool)
{
    DrillTreeNode *node = new DrillTreeNode(DrillTreeNode::Type::IsTool, parent);

    node->tool_ = &tool;
    parent->children_.append(std::move(node));

    return node;
}

void DrillTreeDocumentBuilder::appendHoleNodes(DrillTreeNode *toolNode, const Tool &tool, const DrillDocument &doc)
{
    for (const Hole &hole : doc.holes()) {
        if (hole.toolId != tool.id)
            continue;

        DrillTreeNode* node = new DrillTreeNode(DrillTreeNode::Type::IsHole, toolNode);

        node->hole_ = &hole;
        toolNode->children_.append(std::move(node));
    }
}
