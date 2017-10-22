cmake_minimum_required(VERSION 2.6)
project(tycompiler)

set(tycompiler_VERSION_MAJOR 1)
set(tycompiler_VERSION_MAJOR 0)

include_directories(.)

# tylib
file(GLOB tylib_src ./tylib/src/*.cpp)
file(GLOB tylib_hdr ./tylib/src/*.h ./tylib/*.h)
file(GLOB tylib_hdr_dir ./tylib/src)
file(GLOB tylib_inc_dir ./tylib)
add_library(tylib STATIC ${tylib_src} ${tylib_hdr})

target_include_directories(tylib PRIVATE ${tylib_hdr_dir}) 
target_include_directories(tylib PRIVATE ${tylib_hdr_dir}) 
target_include_directories(tylib PUBLIC ${tylib_inc_dir}) 

# tyex
file(GLOB tyex_src ./tyex/src/*.cpp)
file(GLOB tyex_hdr ./tyex/src/*.h ./tyex/src*.h)

add_executable(ty ${tyex_src} ${tyex_hdr})
target_link_libraries(ty tylib)
