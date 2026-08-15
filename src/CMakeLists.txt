file(GLOB SRC CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

target_sources(DrawEngine PRIVATE ${SRC})

# Include the libraries
target_include_directories(DrawEngine PRIVATE "${DRAW_LIBS}/include")
target_link_libraries(DrawEngine spdlog::spdlog)
target_link_libraries(DrawEngine magic_enum::magic_enum)

# Include all of this projects header files 
target_include_directories(DrawEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
