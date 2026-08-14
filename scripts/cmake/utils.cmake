include(FetchContent)

function(build_third_party_libs)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )

  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.14.1
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
  )

  FetchContent_MakeAvailable(spdlog)
  FetchContent_MakeAvailable(Catch2)
endfunction()

function(set_cmake_prefix_path)
  list(APPEND CMAKE_PREFIX_PATH "${DRAW_LIBS}/include")
endfunction()

function(install_third_party_libs dir)
  message("Copying Headers from ${THIRD_PARTY_SRC} to ${dir}")
  file(COPY
    ${THIRD_PARTY_SRC}/spdlog/include/spdlog
    DESTINATION ${dir}
  )
endfunction()
