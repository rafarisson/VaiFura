find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(VaiFuraExporterGCode STATIC
    GCodeExporter.h
    GCodeExporter.cpp
)

target_link_libraries(VaiFuraExporterGCode PRIVATE
    Qt6::Core
    VaiFuraCore
)

target_include_directories(VaiFuraExporterGCode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
