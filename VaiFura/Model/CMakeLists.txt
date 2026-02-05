find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_add_qml_module(VaiFuraModel
    URI VaiFura.Model
    VERSION 1.0
    STATIC
    SOURCES
        DrillDocumentModel.h
        DrillDocumentModel.cpp
        AbstractToolHoleListModel.h
        ToolListModel.h
        ToolListModel.cpp
        HoleListModel.h
        HoleListModel.cpp
        DrillTreeModel.h
        DrillTreeModel.cpp
        ExportSettingsListModel.h
        ExportSettingsListModel.cpp
)

target_link_libraries(VaiFuraModel
    PRIVATE
        Qt6::Quick
        VaiFuraCore
)

target_include_directories(VaiFuraModel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
