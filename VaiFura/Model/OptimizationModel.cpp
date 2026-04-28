#include "OptimizationModel.h"
#include "DrillDocument.h"
#include "DrillDocumentBuilder.h"
#include "DrillTransformModel.h"

OptimizationModel::OptimizationModel(QObject *parent)
    : QObject{parent}
{}

void OptimizationModel::setOptimizationPlan(AbstractOptimizationPlan *plan)
{
    if (plan_ == plan)
        return;
    plan_ = plan;
    emit optimizationPlanChanged();
}

void OptimizationModel::optimize(const DrillNode* root, const DrillTransformModel *transformModel)
{
    if (!plan_)
        return;

    plan_->optimize(root);

    emit optimizationPlanChanged();
}

void OptimizationModel::generateOptimizedDrillDocument(DrillDocument &out) const
{
    DrillDocumentBuilder builder(&out);
    builder.clear();

    if (!plan_ || plan_->isEmpty())
        return;

    if (plan_->holes().isEmpty() || plan_->order().isEmpty()) {
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

    for (int idx : plan_->order()) {
        if (idx < 0 || idx >= plan_->holes().size())
            continue;

        const auto& ref = plan_->holes()[idx];
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
