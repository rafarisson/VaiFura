find_package(Qt6 REQUIRED COMPONENTS Core Quick)

set(QT_QML_GENERATE_QMLLS_INI ON)

qt_add_qml_module(VaiFuraView
    URI libview
    VERSION 1.0
    STATIC
    SOURCES
        DrillDocumentPreviewQuickItem.h DrillDocumentPreviewQuickItem.cpp
    DEPENDENCIES
        libmodel
)

target_link_libraries(VaiFuraView PRIVATE
    Qt6::Core
    Qt6::Quick
    VaiFuraCore
    VaiFuraModel
)

target_include_directories(VaiFuraView INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
