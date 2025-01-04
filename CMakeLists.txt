cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("PokemonC")

include(FetchContent)

# Dependencies
set(RAYLIB_VERSION 5.0)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

# Add source to this project's executable.
add_executable (PokemonC "src/main.c" "src/constants.h" "src/util/types.h" "src/util/vector.h" "src/util/vector.c" "src/util/hash.h" "src/util/hash.c"   "src/util/set.h" "src/util/set.c" "src/util/util.h" "src/util/util.c" "src/util/map.h" "src/util/map.c" "src/util/texture_pool.h" "src/util/texture_pool.c" "src/ecs/entity_manager.h" "src/ecs/entity_manager.c" "src/ecs/component_manager.h" "src/ecs/components.h" "src/ecs/component_manager.c" "src/ecs/system_manager.h" "src/ecs/system.h" "src/ecs/system_manager.c" "src/ecs/ecs.h" "src/ecs/ecs.c" "src/ecs/components.c" "src/util/camera.h" "src/util/camera.c" "src/ecs/ecs_manager.h" "src/ecs/ecs_manager.c" "src/scene/scene.h" "src/scene/scene.c" "src/scene/world.c" "src/scene/title_screen.c" "src/scene/fire_arena.c" "src/scene/water_arena.c" "src/scene/plant_arena.c" "src/scene/hospital.c" "src/scene/house.c" "src/scene/test_scene_1.c" "src/ecs/system.c" "src/scene/test_scene_2.c" "src/scene/test_scene_3.c" "src/util/debug.h" "src/util/debug.c"
        src/util/tiled_map.h
        src/util/tiled_map.c
        src/util/resource.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if ("${PLATFORM}" STREQUAL "Web")
  add_custom_command(
          TARGET ${PROJECT_NAME} PRE_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/../resources
  )
  #DEPENDS ${PROJECT_NAME}
else()
  add_custom_command(
          TARGET ${PROJECT_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
  )
  #DEPENDS ${PROJECT_NAME}
endif()


#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")
  # Tell Emscripten to build an example.html file.
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
  target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file resources)
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()