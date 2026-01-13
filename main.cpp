#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// #include "DrillDocument.h"
// #include "ToolListModel.h"
// #include "DrillListModel.h"
// #include "ExcellonToolTreeModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // DrillDocument doc;
    // ToolListModel toolsModel;
    // DrillListModel drillsModel;
    // ExcellonToolTreeModel toolsTreeModel;

    // doc.loadFile(R"(C:\Users\xpert\Desktop\drill_1_16.xln)");

    // toolsModel.setModel(doc.model());
    // drillsModel.setModel(doc.model());
    // toolsTreeModel.setModel(doc.model());

    // qDebug() << "tools:" << doc.model()->tools().size() << toolsModel.size()
    //          << "drills" << doc.model()->drills().size() << drillsModel.size();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // engine.rootContext()->setContextProperty("doc", &doc);
    // engine.rootContext()->setContextProperty("toolsModel", &toolsModel);
    // engine.rootContext()->setContextProperty("drillsModel", &drillsModel);
    // engine.rootContext()->setContextProperty("toolsTreeModel", &toolsTreeModel);

    engine.loadFromModule("VaiFura", "Main");

    return app.exec();
}
