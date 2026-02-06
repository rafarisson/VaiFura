find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_library(VaiFuraCore STATIC
    DrillDocument.h
    DrillDocument.cpp
    DrillDocumentBuilder.h
    DrillDocumentBuilder.cpp
    DrillNode.h
    DrillNode.cpp
    DrillParser.h
    DrillExporter.h
    Settings.h
    SettingsRepository.h SettingsRepository.cpp
)

target_link_libraries(VaiFuraCore
    PRIVATE
        Qt6::Core
)

target_include_directories(VaiFuraCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
