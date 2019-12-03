project("HeapLibrary" CXX)                              # Project name
cmake_minimum_required(VERSION 3.5)                     # CMake Version

set(CMAKE_CXX_STANDARD 14)                              # C++ 14
set(CMAKE_CXX_STANDARD_REQUIRED ON)                     # Requested

# COMPILATION FLAGS -----------------------------------------------------------

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if (COMPILER_SUPPORTS_CXX14)
    add_compile_options("-std=c++14")
else()
    message(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
endif()


if (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options("-Wall")
    add_compile_options("-Wextra")
    add_compile_options("-Wpedantic")
    add_compile_options("-Werror")
endif()

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
                  COMMAND cp ${PROJECT_SOURCE_DIR}/build/my_heap ${PROJECT_SOURCE_DIR}/bin/
                  COMMENT "The example file is aviable in bin directory")

add_custom_target(clean-all
                  COMMAND rm -rf ${PROJECT_SOURCE_DIR}/build/*
                  COMMAND rm -rf ${PROJECT_SOURCE_DIR}/doc/*
                  COMMAND rm -rf ${PROJECT_SOURCE_DIR}/bin/*
                  COMMENT "scan-build Static Analysis")

find_program(DOXYGEN_FOUND doxygen)
if (DOXYGEN_FOUND)
    add_custom_target(doc
                      COMMAND doxygen ${PROJECT_SOURCE_DIR}/doxygen.cfg
                      COMMENT "Code documentation")
endif()

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

include_directories(${PROJECT_SOURCE_DIR}/include
                    ${PROJECT_SOURCE_DIR}/lib)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable( my_heap ${SRCS} )

add_library(hp ${SRCS})

add_executable(heap_test EXCLUDE_FROM_ALL
               ${PROJECT_SOURCE_DIR}/tests/test.cpp)
target_link_libraries(heap_test hp)

# TEST DIRECTIVES -------------------------------------------------------------

enable_testing()

add_test(NAME IntHeapMax
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
         COMMAND ./heap_test [IntHeapMax])


add_test(NAME FloatHeapTestMax
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
         COMMAND ./heap_test [FloatHeapTestMax])


add_test(NAME DoubleHeapTestMax
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
         COMMAND ./heap_test [DoubleHeapTestMax])


add_test(NAME IntHeapTestMin
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
         COMMAND ./heap_test [IntHeapTestMin])

          
    find_program(VALGRIND_FOUND valgrind)
    if (VALGRIND_FOUND)

        add_test(NAME ValgrindTest1
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
                COMMAND valgrind --leak-check=full --show-leak-kinds=all
                                --track-origins=yes
                                ./heap_test [IntHeapMax])

        add_test(NAME ValgrindTest2
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
                COMMAND valgrind --leak-check=full --show-leak-kinds=all
                                --track-origins=yes
                                ./heap_test [FloatHeapTestMax])

        add_test(NAME ValgrindTest3
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
                COMMAND valgrind --leak-check=full --show-leak-kinds=all
                                --track-origins=yes
                                ./heap_test [DoubleHeapTestMax])
        add_test(NAME ValgrindTest4
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/build
                COMMAND valgrind --leak-check=full --show-leak-kinds=all
                                --track-origins=yes
                                ./heap_test [IntHeapTestMin])
    endif()
