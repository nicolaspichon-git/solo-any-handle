# solo-any-handle/CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(solo-any-handle
  VERSION 1.0.0
  LANGUAGES CXX
)

# ------------------------------------------------------------------------------
# C++ requirements (C++14 minimum)
# ------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------------------------
# Options
# ------------------------------------------------------------------------------
option(SOLO_ANY_HANDLE_BUILD_TESTS "Build solo-any-handle boost testsuite" ON)

# ------------------------------------------------------------------------------
# solo-any-handle header-only library
# ------------------------------------------------------------------------------

# -- embedded dependency
set(STDEX_BUILD_TESTS OFF CACHE BOOL "Disable stdex tests" FORCE)
add_subdirectory(external/stdex)

add_library(solo-any-handle INTERFACE)
add_library(solo::any_handle ALIAS solo-any-handle)

target_include_directories(solo-any-handle
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/external/stdex/include> # propagate stdex headers
)
target_compile_features(solo-any-handle
  INTERFACE
    cxx_std_14
)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------

# --- Boost (headers only, version check only)

set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost 1.72 REQUIRED)

target_include_directories(solo-any-handle
  INTERFACE
    ${Boost_INCLUDE_DIRS}
)

# --- Stdex (transitive eggs dependency handled internally)
target_link_libraries(solo-any-handle
  INTERFACE stdex::stdex
)

# ---------------------------------------------------a---------------------------
# Installation
# ------------------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  TARGETS solo-any-handle
  EXPORT soloAnyHandleTargets
)

install(
  EXPORT soloAnyHandleTargets
  NAMESPACE solo::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/solo
)

configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/soloAnyHandleConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/soloAnyHandleConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/solo
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/soloAnyHandleConfig.cmake
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/solo
)

# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------

if(SOLO_ANY_HANDLE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
