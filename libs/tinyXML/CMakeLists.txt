# === tinyXML cmake file ===
cmake_minimum_required(VERSION 3.0.2)


include(${PROJECT_SOURCE_DIR}/cmake/remove_cxx_flags.cmake)
remove_cxx_flags(SUPRESS_LIBS_WARNINGS)


set(SOURCES
    tinystr.cpp
    tinyxml.cpp
    tinyxmlerror.cpp
    tinyxmlparser.cpp
)

set(HEADERS
    tinystr.h
    tinyxml.h
)


add_library(tinyXML STATIC ${SOURCES} ${HEADERS} )

target_include_directories(tinyXML
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(tinyXML
    PROPERTIES FOLDER libs
)
