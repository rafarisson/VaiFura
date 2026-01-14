#include "DrillTreeNode.h"

DrillTreeNode::DrillTreeNode(Type type, DrillTreeNode *parent)
    : type_{type}
    , parent_{parent}
{}

DrillTreeNode::~DrillTreeNode()
{
    reset();
}

void DrillTreeNode::reset()
{
    qDeleteAll(children_);
    children_.clear();
}

DrillTreeNode *DrillTreeNode::child(int row) const
{
    return children_.value(row);
}

int DrillTreeNode::row() const
{
    return parent_ ? parent_->children_.indexOf(this) : 0;
}

bool DrillTreeNode::setChecked(bool state)
{
    if (checked_ == state)
        return false;

    checked_ = state;

    // for (auto *child : std::as_const(children_))
    //     child->setChecked(checked_);

    return true;
}
