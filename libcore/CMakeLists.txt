find_package(Qt6 REQUIRED COMPONENTS Core)

set(QT_QML_GENERATE_QMLLS_INI ON)

add_library(VaiFuraCore STATIC
    DrillDocument.h DrillDocument.cpp
    DrillDocumentBuilder.h
    DrillParser.h
    DrillTreeNode.h DrillTreeNode.cpp
    DrillTreeDocument.h DrillTreeDocument.cpp
    DrillTreeDocumentBuilder.h DrillTreeDocumentBuilder.cpp
)

target_link_libraries(VaiFuraCore PRIVATE Qt6::Core)

target_include_directories(VaiFuraCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
