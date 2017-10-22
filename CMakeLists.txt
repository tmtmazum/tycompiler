cmake_minimum_required(VERSION 2.6)
project(tycompiler)

set(tycompiler_VERSION_MAJOR 1)
set(tycompiler_VERSION_MAJOR 0)

include_directories(.)

# tylib
file(GLOB tylib_src ./tylib/src/*.cpp)
file(GLOB tylib_hdr_dir ./tylib/src)
file(GLOB tylib_inc_dir ./tylib)
add_library(tylib STATIC ${tylib_src})

target_include_directories(tylib PRIVATE ${tylib_hdr_dir}) 
target_include_directories(tylib PRIVATE ${tylib_hdr_dir}) 
target_include_directories(tylib PUBLIC ${tylib_inc_dir}) 

# tyex
file(GLOB tyex_src ./tyex/src/*.cpp)

add_executable(ty ${tyex_src})
target_link_libraries(ty tylib)
