cmake_minimum_required(VERSION 3.23)

project(DrawEngine)
add_library(DrawEngine)
include(GNUInstallDirs)

option(DRAWENGINE_BUILD_TESTS "Build tests" OFF)

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

if(DRAWENGINE_BUILD_TESTS)
  find_package(Catch2 CONFIG REQUIRED)

  add_executable(UnitTests
  )

  target_link_libraries(UnitTests
      PRIVATE
          DrawEngine::DrawEngine
          Catch2::Catch2WithMain
  )
  add_subdirectory(tests)
endif()

install(TARGETS DrawEngine
    FILE_SET HEADERS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .so
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .a
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # .dll/.exe
)


