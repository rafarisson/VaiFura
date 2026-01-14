#include "DrillTreeDocument.h"
#include "DrillTreeNode.h"

DrillTreeDocument::DrillTreeDocument()
    : root_{new DrillTreeNode{DrillTreeNode::Type::IsTool}}
{
}

DrillTreeDocument::~DrillTreeDocument()
{
    delete root_;
    root_ = nullptr;
}

void DrillTreeDocument::reset()
{
    root_->reset();
}

