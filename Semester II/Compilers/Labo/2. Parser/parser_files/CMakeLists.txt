#
# Configuration
#

cmake_minimum_required(VERSION 3.0)
project(Cheetah)

# Compilation flags
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11")

# Disable warnings about deleting incomplete pointers; we do this carefully
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-delete-incomplete")


#
# LLVM
#

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Building against LLVM ${LLVM_PACKAGE_VERSION} in ${LLVM_DIR}")
if (NOT ${LLVM_PACKAGE_VERSION} MATCHES "^7.")
    message(FATAL_ERROR "Unsupported LLVM version")
endif()

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Get a hold of llvm-config to check for -DNDEBUG
find_program(LLVM_CONFIG_EXECUTABLE
  NAMES llvm-config llvm-config-${LLVM_VERSION_MAJOR}.${LLVM_VERSION_MINOR}
  HINTS ${LLVM_TOOLS_BINARY_DIR}
  DOC "llvm-config executable"
)
if(NOT LLVM_CONFIG_EXECUTABLE)
  message(FATAL_ERROR "Could NOT find LLVM executable")
endif()

# Check the build type and flags for certain incompatibilities
execute_process(
  COMMAND ${LLVM_CONFIG_EXECUTABLE} --build-mode
  OUTPUT_VARIABLE LLVM_BUILD_TYPE
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE ${LLVM_BUILD_TYPE}
                         CACHE STRING "Choose the type of build."
                         FORCE)
elseif(NOT ${CMAKE_BUILD_TYPE} STREQUAL "${LLVM_BUILD_TYPE}")
  execute_process(
    COMMAND ${LLVM_CONFIG_EXECUTABLE} --cflags
    OUTPUT_VARIABLE LLVM_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  if(${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND
     ${LLVM_CFLAGS} MATCHES "-DNDEBUG")
    MESSAGE(FATAL_ERROR "Requested ${CMAKE_BUILD_TYPE} build incompatible with \
                         LLVM ${LLVM_BUILD_TYPE} build, \
                         which specifies '-DNDEBUG'")
  else()
    message(WARNING "Requested ${CMAKE_BUILD_TYPE} build does not match \
                     LLVM ${LLVM_BUILD_TYPE} build -- \
                     this might cause unexpected behavior")
  endif()
endif()

# NOTE: we link LLVM dynamically, so don't need the list of components
#llvm_map_components_to_libnames(LLVM_LIBRARIES core support option mc X86)


#
# Flex and Bison
#

# Flex command-line options
string(TOUPPER ${CMAKE_BUILD_TYPE} UPPER_BUILD_TYPE)
set(CMAKE_FLEX_FLAGS_DEBUG "--debug")
set(CMAKE_FLEX_FLAGS "${CMAKE_FLEX_FLAGS_${UPPER_BUILD_TYPE}}")

# Bison command-line options
set(CMAKE_BISON_FLAGS_DEBUG "--debug")
set(CMAKE_BISON_FLAGS "${CMAKE_BISON_FLAGS_${UPPER_BUILD_TYPE}} --warnings=all")

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)


#
# Libraries
#

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR})

flex_target(lexer src/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
  COMPILE_FLAGS ${CMAKE_FLEX_FLAGS})
add_library(lexer ${FLEX_lexer_OUTPUTS})

bison_target(parser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
  COMPILE_FLAGS ${CMAKE_BISON_FLAGS})
add_library(parser ${BISON_parser_OUTPUTS})
add_flex_bison_dependency(lexer parser)

add_library(sema src/sema.hpp
                 src/sema/sematype.cpp
                 src/sema/semadecl.cpp
                 src/sema/semastmt.cpp
                 src/sema/semaexpr.cpp)
add_dependencies(sema parser)

add_library(ast src/ast.hpp
                src/ast/decl.hpp
                src/ast/stmt.hpp
                src/ast/expr.hpp src/ast/expr.cpp
                src/ast/loc.hpp src/ast/loc.cpp
                src/ast/dump.cpp)

add_library(auxiliary src/auxiliary.hpp src/auxiliary.cpp)

add_library(driver src/driver.hpp src/driver.cpp)
target_link_libraries(driver lexer parser sema ast auxiliary LLVM)


#
# Executables
#

add_executable(cheetah src/main.cpp)
target_link_libraries(cheetah driver)

if (NOT ${LLVM_ENABLE_RTTI})
    # llvm::cl uses RTTI if available
    set_source_files_properties(src/main.cpp PROPERTIES COMPILE_FLAGS -fno-rtti)
endif()

