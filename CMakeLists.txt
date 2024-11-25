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
add_executable (PokemonC  "src/main.c" "src/constants.h" "src/util/vector.h" "src/util/vector.c" "src/util/avl_tree.h" "src/util/avl_tree.c" "src/util/texture_pool.h" "src/util/texture_pool.c" "src/util/iterator.h" "src/scene/scene.h" "src/util/scene_id.h" "src/scene/scene.c" "src/scene/title_screen.c" "src/scene/world.c" "src/scene/fire_arena.c" "src/scene/plant_arena.c" "src/scene/water_arena.c" "src/scene/hospital.c" "src/scene/house.c" "src/scene/test_scene.c" "src/ecs/components.h" "src/util/types.h" "src/ecs/entity_manager.h" "src/ecs/entity_manager.c" "src/ecs/component_manager.h" "src/ecs/component_manager.c" "src/ecs/system_manager.h" "src/ecs/system_manager.c" "src/util/set.h" "src/util/set.c" "src/ecs/system_sprite.c" "src/ecs/system_sprite_animation.c" "src/util/entity_pair.h" "src/ecs/camera.h" "src/ecs/camera.c" "src/ecs/ecs.h" "src/ecs/ecs.c" "src/ecs/components.c" "src/ecs/ecs_manager.h" "src/ecs/ecs_manager.c" "src/util/tiled_map.h" "src/util/tiled_map.c" "src/util/ObjectID.h" "src/util/CharacterID.h" "src/util/ObjectGroupID.h" "src/ecs/system_character.c" "src/ecs/system_movement.c" "src/ecs/system_coast.c" "src/ecs/system_player.c" "src/ecs/system_water.c" "src/ecs/system_transition.c" "src/util/tile.h" "src/util/map_info.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET PokemonC PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

