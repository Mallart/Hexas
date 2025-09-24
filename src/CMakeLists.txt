cmake_minimum_required(VERSION 3.31)
project(hexas_compiler)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(
    -g 
    -O0 
    #-Wall -Wextra -Wpedantic 
    -Wno-unknown-pragmas
)


file(GLOB_RECURSE hexas_sources CONFIGURE_DEPENDS
    assembler/*.c
    data/*.c
)

add_executable(hexas ./main.c ${hexas_sources})

target_link_libraries(hexas PRIVATE m)

install(TARGETS hexas DESTINATION CMAKE_INSTALL_PREFIX)