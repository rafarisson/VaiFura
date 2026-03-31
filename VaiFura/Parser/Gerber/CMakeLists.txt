find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(VaiFuraParserGerber STATIC
    DimensionOutline.h DimensionOutline.cpp
)

target_link_libraries(VaiFuraParserGerber PRIVATE
    Qt6::Core
    VaiFuraCore
)

target_include_directories(VaiFuraParserGerber INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
