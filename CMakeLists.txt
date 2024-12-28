# CMakeList.txt : CMake project for PokemonC, include source and define
# project specific logic here.
#
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
add_executable (PokemonC "src/main.c" "src/constants.h" "src/util/util.h" "src/util/util.c" "src/scene/scene_id.h" "src/scene/scene.h" "src/scene/scene.c" "src/util/config.h" "src/util/config.c" "src/scene/title_screen.c" "src/scene/world.c" "src/scene/fire_arena.c" "src/scene/plant_arena.c" "src/scene/water_arena.c" "src/scene/hospital.c" "src/scene/house.c" "src/scene/test_scene.c" "src/util/types.h" "src/util/vector.h" "src/util/iterator.h" "src/util/vector.c" "src/util/set.h" "src/util/set.c" "src/util/map.h" "src/util/map.c" "src/util/texture_pool.h" "src/util/texture_pool.c" "src/ecs/components.h" "src/ecs/components.c" "src/ecs/component_manager.h" "src/ecs/component_manager.c" "src/ecs/entity_manager.h" "src/ecs/entity_manager.c" "src/ecs/system.h" "src/ecs/system_manager.h" "src/ecs/system_manager.c" "src/util/entity_pair.h" "src/util/entity_pair.c" "src/ecs/camera.h" "src/ecs/camera.c" "src/ecs/ecs.h" "src/ecs/ecs.c" "src/ecs/system.c" "src/ecs/ecs_manager.h" "src/ecs/ecs_manager.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PokemonC PROPERTY CXX_STANDARD 20)
endif()


add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)