find_package(Qt6 REQUIRED COMPONENTS Core Gui)

qt_add_library(VaiFuraOptimization STATIC
    NearestNeighborOptimization.h NearestNeighborOptimization.cpp
    NoneOptimization.h NoneOptimization.cpp
    NearestNeighbor2OptOptimization.h NearestNeighbor2OptOptimization.cpp
)

target_link_libraries(VaiFuraOptimization
    PRIVATE
        Qt6::Core
        Qt6::Gui
        VaiFuraCore
)

target_include_directories(VaiFuraOptimization INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
