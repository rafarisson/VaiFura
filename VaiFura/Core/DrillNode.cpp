#include "DrillNode.h"

DrillNode::DrillNode(Type type, DrillNode *parent)
    : type_{type}
    , parent_{parent}
{}

DrillNode::~DrillNode()
{
    clear();
}

void DrillNode::clear()
{
    qDeleteAll(children_);
    children_.clear();
}

int DrillNode::row() const
{
    return parent_ ? parent_->children_.indexOf(this) : 0;
}

bool DrillNode::setCheckState(Qt::CheckState newState)
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

void DrillNode::updateParent()
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
