find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(VaiFuraParserExcellon STATIC
    ExcellonToken.h
    ExcellonLexer.cpp ExcellonLexer.h
    ExcellonDrillParser.cpp ExcellonDrillParser.h
)

target_link_libraries(VaiFuraParserExcellon PRIVATE
    Qt6::Core
    VaiFuraCore
)

target_include_directories(VaiFuraParserExcellon INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
