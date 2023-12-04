cmake_minimum_required(VERSION 3.14)

project("learn-sdl")

add_subdirectory("deps/SDL")
add_subdirectory("deps/SDL_image")

file(GLOB PROJECT_SOURCES "*.*pp")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE
        "deps/SDL/include" "deps/SDL_image/include")
target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL3::SDL3 SDL3_image::SDL3_image)

if (WIN32)
        add_custom_command(TARGET ${PROJECT_NAME}
                POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
                COMMAND_EXPAND_LISTS)
endif ()

file(GLOB PROJECT_RESOURCES "rsc/*")
foreach (RES_PATH ${PROJECT_RESOURCES})
    get_filename_component(RES_NAME ${RES_PATH} NAME)
    configure_file(${RES_PATH} "${CMAKE_BINARY_DIR}/rsc/${RES_NAME}" COPYONLY)
endforeach ()
