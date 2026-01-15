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

bool DrillTreeNode::setCheckState(Qt::CheckState newState)
{
    if (state_ == newState)
        return false;

    state_ = newState;

    if (state_ != Qt::PartiallyChecked) {
        for (auto *child : std::as_const(children_))
            child->setCheckState(newState);
    }

    if (parent_)
        parent_->updateParent();

    return true;
}

void DrillTreeNode::updateParent()
{
    Qt::CheckState newParentState = Qt::PartiallyChecked;
    int checkedCounter = 0;
    int uncheckedCounter = 0;

    for (auto *child : std::as_const(children_)) {
        switch (child->checkState()) {
        case Qt::Checked:
            checkedCounter++;
            break;
        case Qt::Unchecked:
            uncheckedCounter++;
            break;
        case Qt::PartiallyChecked:
            break;
        }
    }

    if (checkedCounter == children_.size())
        newParentState = Qt::Checked;
    else if (uncheckedCounter == children_.size())
        newParentState = Qt::Unchecked;

    state_ = newParentState;

    if (parent_)
        parent_->updateParent();
}
