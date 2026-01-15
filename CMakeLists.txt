cmake_minimum_required(VERSION 3.16)

project(VaiFura VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick)
find_package(Qt6 REQUIRED COMPONENTS Core)

set(QT_QML_GENERATE_QMLLS_INI ON)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(libcore)
add_subdirectory(libexcellon)
add_subdirectory(libmodel)
add_subdirectory(libview)

qt_add_executable(appVaiFura
    main.cpp
)

qt_add_qml_module(appVaiFura
    URI VaiFura
    VERSION 1.0
    QML_FILES
        Main.qml
        DrillTreeViewDelegate.qml
    SOURCES
        VaiFuraSingleton.h VaiFuraSingleton.cpp
    DEPENDENCIES
        libmodel
        libview
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
        VaiFuraExcellon
        VaiFuraModel
        VaiFuraView
)
target_link_libraries(appVaiFura PRIVATE Qt6::Core)

include(GNUInstallDirs)
install(TARGETS appVaiFura
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
