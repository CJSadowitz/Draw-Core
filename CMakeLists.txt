cmake_minimum_required(VERSION 3.23)

project(DrawEngine)
add_library(DrawEngine)
include(GNUInstallDirs)

# User provided build options
option(DRAWENGINE_BUILD_TESTS "Build tests" OFF)
option(INSTALL_THIRD_PARTY_LIBS "Install third party libs" OFF)

# Run the cmake file inside of the third_party directory
if(INSTALL_THIRD_PARTY_LIBS)
  add_subdirectory(third_party)
endif

# Attach the built unittesting library and generate test cases
if(DRAWENGINE_BUILD_TESTS)
  find_package(Catch2 CONFIG REQUIRED)
  add_subdirectory(tests)
endif()

# Recursively do this?
target_sources(DrawEngine
  PRIVATE
    src/DrawEngine.cxx
    src/TurnState.cxx

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/DrawEngine.hpp
      include/TurnState.hpp
  )

target_include_directories(DrawEngine
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )

install(TARGETS DrawEngine
    FILE_SET HEADERS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .so
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .a
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # .dll/.exe
)


