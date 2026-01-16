#ifndef DRILLNODE_H
#define DRILLNODE_H

#include <QVector>

class Tool;
class Hole;

class DrillNode
{
public:
    enum class Type {
        IsTool,
        IsHole
    };

    explicit DrillNode(Type type, DrillNode *parent = nullptr);
    ~DrillNode();

    void clear();

    Type type() const { return type_; }
    DrillNode *child(int row) { return children_.value(row); }
    const DrillNode *child(int row) const { return children_.value(row); }
    const DrillNode *parent() const { return parent_; };
    int childCount() const { return children_.size(); }
    int row() const;

    const Tool *tool() const { return tool_; }
    const Hole *hole() const { return hole_; }

    bool isChecked() const { return state_ != Qt::Unchecked; }
    Qt::CheckState checkState() const { return state_; }
    bool setCheckState(Qt::CheckState newState);

private:
    friend class DrillDocumentBuilder;
    friend class DrillTreeDocumentBuilder;

    void updateParent();

    Type type_;
    DrillNode *parent_ = nullptr;
    QVector<DrillNode*> children_;
    const Tool *tool_ = nullptr;
    const Hole *hole_ = nullptr;
    Qt::CheckState state_ = Qt::Checked;
};

#endif // DRILLNODE_H
