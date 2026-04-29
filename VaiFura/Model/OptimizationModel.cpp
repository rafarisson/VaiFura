#include "OptimizationModel.h"
#include "DrillDocument.h"
#include "DrillDocumentBuilder.h"
#include "DrillTransformModel.h"

OptimizationModel::OptimizationModel(QObject *parent)
    : QObject{parent}
    , currentIndex_{-1}
{}

OptimizationModel::~OptimizationModel()
{
    qDeleteAll(plans_);
    plans_.clear();
}

QStringList OptimizationModel::availablePlans() const
{
    QStringList list;
    for (const auto &p : plans_)
        list << p->name();
    return list;
}

void OptimizationModel::setCurrentPlanIndex(int index)
{
    if (currentIndex_ == index)
        return;
    currentIndex_ = index;
    emit currentPlanIndexChanged();
    emit currentPanChanged();
}

void OptimizationModel::addPlan(AbstractOptimizationPlan *plan)
{
    plans_.append(plan);

    if (currentIndex_ == -1)
        setCurrentPlanIndex(0);

    emit availablePlansChanged();
}

AbstractOptimizationPlan *OptimizationModel::currentPlan() const
{
    return currentIndex_ >= 0 && currentIndex_ < plans_.size() ? plans_[currentIndex_] : nullptr;
}

void OptimizationModel::optimize(const DrillNode* root, const DrillTransformModel *transformModel)
{
    auto plan = currentPlan();
    if (!plan)
        return;

    plan->optimize(root, transformModel ? transformModel->transform() : nullptr);
    emit optimized();
}

void OptimizationModel::generateOptimizedDrillDocument(DrillDocument &out) const
{
    DrillDocumentBuilder builder(&out);
    builder.clear();

    auto plan = currentPlan();
    if (!plan || plan->isEmpty())
        return;

    if (plan->holes().isEmpty() || plan->order().isEmpty()) {
        builder.build();
        return;
    }

    // QHash<int, Tool> toolMap;

    // for (const auto& ref : holes()) {
    //     const DrillNode* holeNode = ref.node;
    //     if (!holeNode)
    //         continue;

    //     const DrillNode* toolNode = holeNode->parent();
    //     if (!toolNode)
    //         continue;

    //     const Tool* tool = toolNode->tool();
    //     if (!tool)
    //         continue;

    //     toolMap.insert(tool->id, *tool);
    // }

    // for (auto it = toolMap.begin(); it != toolMap.end(); ++it) {
    //     builder.addTool(it.value());
    // }

    builder.addTool(Tool{1, 1});

    for (int idx : plan->order()) {
        if (idx < 0 || idx >= plan->holes().size())
            continue;

        const auto& ref = plan->holes()[idx];
        const DrillNode* holeNode = ref.node;
        if (!holeNode)
            continue;

        const Hole* hole = holeNode->hole();
        if (!hole)
            continue;

        builder.addHole({
            ref.pos.x(),
            ref.pos.y(),
            1
        });
    }

    builder.build();
}
