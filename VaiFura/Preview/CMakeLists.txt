find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_add_qml_module(VaiFuraPreview
    URI VaiFura.Preview
    VERSION 1.0
    STATIC
    SOURCES
        ViewportTransform.h
        ViewportTransform.cpp
        SnapEngine.h
        SnapEngine.cpp
        InteractionController.h
        InteractionController.cpp
        SnapPreviewRenderer.h
        GridRenderer.h
        GridRenderer.cpp
        OriginRenderer.h
        OriginRenderer.cpp
        DrillHelper.h
        DrillRendererBase.h
        DrillRendererBase.cpp
        DrillRenderer.h
        DrillRenderer.cpp
        DrillDocumentPreviewQuickItem.h
        DrillDocumentPreviewQuickItem.cpp
    DEPENDENCIES
        TARGET VaiFuraModel
)

target_link_libraries(VaiFuraPreview
    PRIVATE
        Qt6::Core
        Qt6::Quick
        VaiFuraCore
        VaiFuraModel
)

target_include_directories(VaiFuraPreview INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
