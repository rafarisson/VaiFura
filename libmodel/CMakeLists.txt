find_package(Qt6 REQUIRED COMPONENTS Core Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(QT_QML_GENERATE_QMLLS_INI ON)

qt_add_qml_module(VaiFuraModel
    URI libmodel
    VERSION 1.0
    STATIC
    SOURCES
        AbstractDrillListModel.h
        ToolListModel.h ToolListModel.cpp
        DrillListModel.h DrillListModel.cpp
        DrillDocument.h DrillDocument.cpp
        DrillTreeItem.h DrillTreeItem.cpp
        DrillTreeModel.h DrillTreeModel.cpp
)

target_link_libraries(VaiFuraModel PRIVATE
    Qt6::Core
    Qt6::Quick
    VaiFuraCore
    VaiFuraExcellon
)
target_link_libraries(VaiFuraModel PRIVATE Qt6::Core)

target_include_directories(VaiFuraModel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
