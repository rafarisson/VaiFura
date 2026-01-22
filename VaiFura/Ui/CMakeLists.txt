find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_add_qml_module(VaiFuraUi
    URI VaiFura.Ui
    VERSION 1.0
    STATIC
    QML_FILES
        Components/Preview.qml
        Components/DrillTreeViewDelegate.qml
        PageDrills.qml
    DEPENDENCIES
        TARGET VaiFuraModel
        TARGET VaiFuraPreview
)

target_link_libraries(VaiFuraUi
    PRIVATE
        Qt6::Core
        Qt6::Quick
        VaiFuraModel
        VaiFuraPreview
)

target_include_directories(VaiFuraUi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
