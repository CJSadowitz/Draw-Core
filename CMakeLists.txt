cmake_minimum_required(VERSION 3.22)

project(DrawEngine VERSION 1.0.0 LANGUAGES CXX)
add_library(DrawEngine STATIC)
include(GNUInstallDirs)

# User provided build options
option(DRAWENGINE_BUILD_TESTS "Build tests" OFF)
option(INSTALL_THIRD_PARTY_LIBS "Install third party libs" OFF)

# Run the cmake file inside of the third_party directory
if(INSTALL_THIRD_PARTY_LIBS)
  add_subdirectory(third_party)
endif()

# Attach the built unittesting library and generate test cases
if(DRAWENGINE_BUILD_TESTS)
  add_subdirectory(tests)
endif()

target_sources(DrawEngine
  PRIVATE
    src/DrawEngine.cpp
    src/TurnState.cpp
)

target_include_directories(DrawEngine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
  TARGETS DrawEngine
  EXPORT DrawEngine
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

add_library(DrawEngine::DrawEngine ALIAS DrawEngine)

install(
  EXPORT DrawEngine
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DrawEngine
  NAMESPACE DrawEngine::
  FILE DrawEngine.cmake
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/DrawEngineConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/DrawEngineConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DrawEngine
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/DrawEngineConfigVersion.cmake
  VERSION 1.0.0
  COMPATIBILITY SameMajorVersion
  )

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/DrawEngineConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/DrawEngineConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/DrawEngine"
  )

