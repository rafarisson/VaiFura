find_package(Qt6 REQUIRED COMPONENTS Core Quick)

set_source_files_properties(
    MaterialIcons/MaterialIcons.qml
    MaterialSymbols/MaterialSymbols.qml
    PROPERTIES
        QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(VaiFuraUi
    URI VaiFura.Ui
    VERSION 1.0
    STATIC
    QML_FILES
        Components/PageLayout.qml
        Components/Preview.qml
        Components/DrillTreeViewDelegate.qml
        Components/UnitTextField.qml
        Components/PageHeader.qml
        Components/HelpToolTip.qml
        MaterialIcons/MaterialIcons.qml
        MaterialSymbols/MaterialSymbols.qml
        PageDrills.qml
        PageOffset.qml
        PageExport.qml
    DEPENDENCIES
        TARGET VaiFuraModel
        TARGET VaiFuraPreview
    RESOURCES
        MaterialIcons/materialdesignicons-webfont.ttf
        MaterialSymbols/MaterialSymbolsOutlined.ttf
)

target_link_libraries(VaiFuraUi
    PRIVATE
        Qt6::Core
        Qt6::Quick
        VaiFuraModel
        VaiFuraPreview
)

target_include_directories(VaiFuraUi INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
