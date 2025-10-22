cmake_minimum_required(VERSION 3.10)
project(colors C CXX)

set(COLORS_BASE_DIR     ${CMAKE_CURRENT_LIST_DIR})
set(COLORS_SRC_DIR      "${COLORS_BASE_DIR}/src")
set(COLORS_INC_DIR      "${COLORS_BASE_DIR}/inc")
set(COLORS_INC_INT_DIR  "${COLORS_INC_DIR}/colors")
set(COLORS_LIB_DIR      "${COLORS_BASE_DIR}/lib")
set(COLORS_FIXMATH_DIR  "${COLORS_LIB_DIR}/libfixmath")

set(COLORS_SOURCES
    "${COLORS_SRC_DIR}/hsv.cxx"
    "${COLORS_SRC_DIR}/rgb.cxx"
)

set(COLORS_INCLUDE_DIRS
    PRIVATE     ${COLORS_INC_INT_DIR}
    INTERFACE   ${COLORS_INC_DIR}
)

add_subdirectory(${COLORS_FIXMATH_DIR})
target_compile_definitions(libfixmath PRIVATE
    FIXMATH_NO_64BIT
    FIXMATH_NO_CACHE
    FIXMATH_OPTIMIZE_8BIT
    FIXMATH_NO_OVERFLOW
    FIXMATH_NO_ROUNDING
)

add_library(colors ${COLORS_SOURCES})
target_include_directories(colors ${COLORS_INCLUDE_DIRS})
target_link_libraries(colors PUBLIC libfixmath)