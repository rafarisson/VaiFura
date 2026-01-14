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

    bool isChecked() const { return checked_; }
    bool setChecked(bool state);

private:
    friend class DrillTreeDocumentBuilder;

    Type type_;
    DrillTreeNode *parent_ = nullptr;
    QVector<DrillTreeNode*> children_;
    const Tool *tool_ = nullptr;
    const Hole *hole_ = nullptr;
    bool checked_ = true;
};

#endif // DRILLTREENODE_H
