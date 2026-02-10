cmake_minimum_required(VERSION 3.16)

project(VaiFura VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)

qt_standard_project_setup(REQUIRES 6.10)

add_subdirectory(VaiFura/Core)
add_subdirectory(VaiFura/Model)
add_subdirectory(VaiFura/Preview)
add_subdirectory(VaiFura/Ui)
add_subdirectory(VaiFura/Parser/Excellon)
add_subdirectory(VaiFura/Exporter/GCode)

qt_add_executable(appVaiFura
    "${CMAKE_CURRENT_SOURCE_DIR}/VaiFura.rc"
    main.cpp
)

qt_add_resources(appVaiFura "style"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

qt_add_qml_module(appVaiFura
    URI VaiFura
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        VaiFuraSingleton.h VaiFuraSingleton.cpp
    DEPENDENCIES
        TARGET VaiFuraModel
        TARGET VaiFuraPreview
        TARGET VaiFuraUi
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appVaiFura PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appVaiFura
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appVaiFura
    PRIVATE
        Qt6::Core
        Qt6::Quick
        VaiFuraCore
        VaiFuraModel
        VaiFuraPreview
        VaiFuraUi
        VaiFuraParserExcellon
        VaiFuraExporterGCode
)

include(GNUInstallDirs)
install(TARGETS appVaiFura
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
