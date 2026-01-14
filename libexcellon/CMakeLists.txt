find_package(Qt6 REQUIRED COMPONENTS Core)

set(QT_QML_GENERATE_QMLLS_INI ON)

add_library(VaiFuraExcellon STATIC
    ExcellonToken.h
    ExcellonLexer.cpp ExcellonLexer.h
    ExcellonDrillParser.cpp ExcellonDrillParser.h
)

target_link_libraries(VaiFuraExcellon PRIVATE
    Qt6::Core
    VaiFuraCore
)

target_include_directories(VaiFuraExcellon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
