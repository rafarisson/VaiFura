#include "DrillDocumentBuilder.h"

DrillDocumentBuilder::DrillDocumentBuilder(DrillDocument *document)
    : doc_{document}
{
    clear();
}

void DrillDocumentBuilder::addTool(const Tool &tool)
{
    doc_->tools_.append(tool);
}

void DrillDocumentBuilder::addHole(const Hole &hole)
{
    doc_->holes_.append(hole);
}

void DrillDocumentBuilder::clear()
{
    doc_->clear();
    doc_->root_.clear();
}

void DrillDocumentBuilder::build()
{
    doc_->root_.clear();
    for (const Tool &tool : doc_->tools()) {
        DrillNode *toolNode = createToolNode(&doc_->root_, tool);
        appendHoleNodes(toolNode, tool, doc_->holes());
    }
}

DrillNode *DrillDocumentBuilder::createToolNode(DrillNode *parent, const Tool &tool)
{
    auto *node = new DrillNode(DrillNode::Type::IsTool, parent);

    node->tool_ = &tool;
    parent->children_.append(node);

    return node;
}

void DrillDocumentBuilder::appendHoleNodes(DrillNode *toolNode, const Tool &tool, const QVector<Hole> &holes)
{
    for (const Hole &hole : holes) {
        if (hole.toolId != tool.id)
            continue;

        auto *node = new DrillNode(DrillNode::Type::IsHole, toolNode);

        node->hole_ = &hole;
        toolNode->children_.append(node);
    }
}
