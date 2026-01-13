#ifndef VAIFURASINGLETON_H
#define VAIFURASINGLETON_H

#include <QObject>
#include <QQmlEngine>

#include "DrillDocument.h"
#include "ToolListModel.h"
#include "DrillListModel.h"

class VaiFuraSingleton : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(VaiFura)

    Q_PROPERTY(DrillDocument* drillDoc READ drillDoc CONSTANT FINAL)
    Q_PROPERTY(ToolListModel *toolListModel READ toolListModel CONSTANT FINAL)
    Q_PROPERTY(DrillListModel *drillListModel READ drillListModel CONSTANT FINAL)

public:
    explicit VaiFuraSingleton(QObject *parent = nullptr);

    DrillDocument* drillDoc() const { return drillDoc_; }
    ToolListModel* toolListModel() const { return toolListModel_; }
    DrillListModel* drillListModel() const { return drillListModel_; }

signals:

private:
    DrillDocument *drillDoc_ = nullptr;
    ToolListModel *toolListModel_ = nullptr;
    DrillListModel *drillListModel_ = nullptr;
};

#endif // VAIFURASINGLETON_H
