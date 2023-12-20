cmake_minimum_required(VERSION 3.14)

project("sdl-samples")

file(GLOB PROJECT_SOURCES "src/*")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14)

# SDL

add_subdirectory("deps/SDL")
target_include_directories(${PROJECT_NAME} PRIVATE "deps/SDL/include")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

# SDL_Image

add_subdirectory("deps/SDL_image")
target_include_directories(${PROJECT_NAME} PRIVATE "deps/SDL_image/include")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_image::SDL3_image)

# Copy dlls into build dir

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
            COMMAND_EXPAND_LISTS)
endif ()

# Copy resources

file(GLOB PROJECT_RESOURCES "rsc/*")
foreach (RES_PATH ${PROJECT_RESOURCES})
    get_filename_component(RES_NAME ${RES_PATH} NAME)
    configure_file(${RES_PATH} "${CMAKE_BINARY_DIR}/rsc/${RES_NAME}" COPYONLY)
endforeach ()
