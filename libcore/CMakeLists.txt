find_package(Qt6 REQUIRED COMPONENTS Core)

set(QT_QML_GENERATE_QMLLS_INI ON)

add_library(VaiFuraCore STATIC
    VaiFuraTypes.h
    DrillModel.h
    DrillBuilder.h
    AbstractDrillParser.h
)

target_link_libraries(VaiFuraCore PRIVATE Qt6::Core)

target_include_directories(VaiFuraCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
