cmake_minimum_required(VERSION 3.28)
project(pe_converter)

set(CMAKE_CXX_STANDARD 17)

# 对于 Release 模式，使用 /MT
# 对于 Debug 模式，使用 /MTd
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd /Zi /Ob0 /Od /RTC1 /GS /GL /sdl")
else()
    set(CMAKE_CXX_FLAGS_RELEASE "/MT /O2 /Ob2 /Oi /Ot /Oy /GS /GL /sdl")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(libpeconv/include)

set(SOURCES
        main.cpp
        libpeconv/src/pe_hdrs_helper.cpp
        libpeconv/src/pe_mode_detector.cpp
        libpeconv/src/pe_raw_to_virtual.cpp
        libpeconv/src/pe_virtual_to_raw.cpp
        libpeconv/src/relocate.cpp
        libpeconv/src/buffer_util.cpp
        libpeconv/src/remote_pe_reader.cpp
        libpeconv/src/imports_loader.cpp
        libpeconv/src/delayed_imports_loader.cpp
        libpeconv/src/fix_imports.cpp
        libpeconv/src/pe_loader.cpp
        libpeconv/src/pe_dumper.cpp
        libpeconv/src/exports_lookup.cpp
        libpeconv/src/function_resolver.cpp
        libpeconv/src/hooks.cpp
        libpeconv/src/exported_func.cpp
        libpeconv/src/exports_mapper.cpp
        libpeconv/src/resource_parser.cpp
        libpeconv/src/file_util.cpp
        libpeconv/src/resource_util.cpp
        libpeconv/src/imports_uneraser.cpp
        libpeconv/src/load_config_util.cpp
        libpeconv/src/caves.cpp
        libpeconv/src/util.cpp
        libpeconv/src/fix_dot_net_ep.cpp
        libpeconv/src/find_base.cpp
        libpeconv/src/peb_lookup.cpp
        libpeconv/src/tls_parser.cpp
        libpeconv/src/exceptions_parser.cpp
)

# 所有的头文件 (可选，但添加进来有助于 IDE 识别)
set(HEADERS
        libpeconv/include/peconv.h
        libpeconv/include/peconv/pe_hdrs_helper.h
        libpeconv/include/peconv/pe_mode_detector.h
        libpeconv/include/peconv/pe_raw_to_virtual.h
        libpeconv/include/peconv/pe_virtual_to_raw.h
        libpeconv/include/peconv/relocate.h
        libpeconv/include/peconv/util.h
        libpeconv/include/peconv/buffer_util.h
        libpeconv/include/peconv/remote_pe_reader.h
        libpeconv/include/peconv/imports_loader.h
        libpeconv/include/peconv/delayed_imports_loader.h
        libpeconv/include/peconv/fix_imports.h
        libpeconv/include/peconv/pe_loader.h
        libpeconv/include/peconv/pe_dumper.h
        libpeconv/include/peconv/exports_lookup.h
        libpeconv/include/peconv/function_resolver.h
        libpeconv/include/peconv/hooks.h
        libpeconv/include/peconv/exported_func.h
        libpeconv/include/peconv/exports_mapper.h
        libpeconv/include/peconv/resource_parser.h
        libpeconv/include/peconv/file_util.h
        libpeconv/include/peconv/resource_util.h
        libpeconv/include/peconv/imports_uneraser.h
        libpeconv/include/peconv/load_config_util.h
        libpeconv/include/peconv/load_config_defs.h
        libpeconv/include/peconv/caves.h
        libpeconv/include/peconv/find_base.h
        libpeconv/include/peconv/peb_lookup.h
        libpeconv/include/peconv/tls_parser.h
        libpeconv/include/peconv/exceptions_parser.h
        libpeconv/include/peconv/unicode.h
        libpeconv/src/fix_dot_net_ep.h
)

add_executable(pe_converter ${SOURCES} ${HEADERS})