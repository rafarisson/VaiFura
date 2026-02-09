find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_library(VaiFuraCore STATIC
    DrillHelper.h
    DrillDocument.h
    DrillDocument.cpp
    DrillDocumentBuilder.h
    DrillDocumentBuilder.cpp
    DrillNode.h
    DrillNode.cpp
    DrillParser.h
    Settings.h
    Settings.cpp
    SettingsRepository.h
    SettingsRepository.cpp
    SettingsReader.h
)

target_link_libraries(VaiFuraCore
    PRIVATE
        Qt6::Core
)

target_include_directories(VaiFuraCore INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
