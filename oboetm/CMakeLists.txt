cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(
        -fexceptions
        -frtti
        -std=c++17)

file(GLOB oboetm_SRC CONFIGURE_DEPENDS *.cpp)
add_library(oboetm STATIC ${oboetm_SRC})

target_include_directories(oboetm PUBLIC .)
target_include_directories(react_codegen_NativeOboe PUBLIC .)
set (OBOE_DIR ./oboe)
add_subdirectory (${OBOE_DIR} ./oboe)
include_directories (${OBOE_DIR}/include)

target_link_libraries(oboetm
        jsi
        reactnative
        react_codegen_NativeOboe
        log
        oboe
        )