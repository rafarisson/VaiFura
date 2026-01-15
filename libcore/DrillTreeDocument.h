#ifndef DRILLTREEDOCUMENT_H
#define DRILLTREEDOCUMENT_H

class DrillTreeNode;

class DrillTreeDocument
{
public:
    explicit DrillTreeDocument();
    ~DrillTreeDocument();

    DrillTreeDocument(const DrillTreeDocument&) = delete;
    DrillTreeDocument& operator=(const DrillTreeDocument&) = delete;

    void reset();
    DrillTreeNode *root() const { return root_; }

private:
    DrillTreeNode *root_;
};

#endif // DRILLTREEDOCUMENT_H
