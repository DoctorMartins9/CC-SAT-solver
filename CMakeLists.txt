project("CC-SAT_solver" CXX)                            # Project name
cmake_minimum_required(VERSION 3.5)                     # CMake Version

set(CMAKE_CXX_STANDARD 14)                              # C++ 14
set(CMAKE_CXX_STANDARD_REQUIRED ON)                     # Requested

# COMPILATION FLAGS -----------------------------------------------------------

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if (COMPILER_SUPPORTS_CXX14)
    add_compile_options("-std=c++14")
    add_compile_options("-pthread")
else()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
endif()
find_package (Threads)

# BUILD MODE ------------------------------------------------------------------
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options("-O3")

elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
    if (CMAKE_COMPILER_IS_GNUCXX)
        add_compile_options("-ggdb3")
    elseif (CMAKE_CXX_COMPILER_ID EQUAL "Clang")
        add_compile_options("-ggdb")
    else()
        add_compile_options("-g")
    endif()

elseif (CMAKE_BUILD_TYPE STREQUAL "SANITIZE" AND
        CMAKE_CXX_COMPILER_ID EQUAL "Clang")

    add_compile_options("-O1")
    add_compile_options("-g")
    add_compile_options("-fno-omit-frame-pointer")
    add_compile_options("-fno-optimize-sibling-calls")

    add_compile_options("-fsanitize=address")
    add_compile_options("-fsanitize=leak")
    add_compile_options("-fsanitize=memory")
    add_compile_options("-fsanitize-memory-track-origins")
    add_compile_options("-fsanitize=undefined")
    add_compile_options("-fsanitize=integer")
    add_compile_options("-fsanitize=nullability")

    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

# CUSTOM TARGETS --------------------------------------------------------------

add_custom_target(release
                  COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/bin
                  COMMAND make all
                  COMMAND cp ${PROJECT_SOURCE_DIR}/build/ccsat ${PROJECT_SOURCE_DIR}/bin/
                  COMMAND cp ${PROJECT_SOURCE_DIR}/build/validation ${PROJECT_SOURCE_DIR}/bin/
                  COMMAND cp ${PROJECT_SOURCE_DIR}/build/benchmark ${PROJECT_SOURCE_DIR}/bin/
                  COMMENT "The example files are aviable in bin directory")

add_custom_target(clean-all
                  COMMAND rm -rf ${PROJECT_SOURCE_DIR}/build/*
                  COMMAND rm -rf ${PROJECT_SOURCE_DIR}/bin/*
                  COMMENT "scan-build Static Analysis")

find_program(CLANGTIDY_FOUND clang-tidy)
if (CLANGTIDY_FOUND)
    add_custom_target(tidy
                      COMMAND clang-tidy -p=.
                              ../src/*.cpp ../test/*.cpp
                      COMMENT "clang-tidy Linter")
endif()

find_program(LYZARD_FOUND lizard)
if (LYZARD_FOUND)
    add_custom_target(cyclo
                      COMMAND lizard ${PROJECT_SOURCE_DIR}/src/
                                     ${PROJECT_SOURCE_DIR}/include/
                      COMMENT "Code Complexity")
endif()

# BUILD TARGETS ---------------------------------------------------------------

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/main.cpp)
add_executable( ccsat ${SRCS} )
target_link_libraries (ccsat ${CMAKE_THREAD_LIBS_INIT})

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/tests/test.cpp)
add_executable( validation ${SRCS} )
target_link_libraries (validation ${CMAKE_THREAD_LIBS_INIT})

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/benchmark.cpp)
add_executable( benchmark ${SRCS} )
target_link_libraries (benchmark ${CMAKE_THREAD_LIBS_INIT})

add_library(cc_sat ${SRCS})
