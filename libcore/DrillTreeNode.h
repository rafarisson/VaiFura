#ifndef DRILLTREENODE_H
#define DRILLTREENODE_H

#include <QVector>

class Tool;
class Hole;

class DrillTreeNode
{
public:
    enum class Type {
        IsTool,
        IsHole
    };

    explicit DrillTreeNode(Type type, DrillTreeNode *parent = nullptr);
    ~DrillTreeNode();

    void reset();

    Type type() const { return type_; }
    DrillTreeNode *child(int row) const;
    DrillTreeNode *parent() const { return parent_; };
    int childCount() const { return children_.size(); }
    int row() const;

    const Tool *tool() const { return tool_; }
    const Hole *hole() const { return hole_; }

    bool isChecked() const { return state_ != Qt::Unchecked; }
    Qt::CheckState checkState() const { return state_; }
    bool setCheckState(Qt::CheckState newState);

private:
    friend class DrillTreeDocumentBuilder;

    void updateParent();

    Type type_;
    DrillTreeNode *parent_ = nullptr;
    QVector<DrillTreeNode*> children_;
    const Tool *tool_ = nullptr;
    const Hole *hole_ = nullptr;
    Qt::CheckState state_ = Qt::Checked;
};

#endif // DRILLTREENODE_H
