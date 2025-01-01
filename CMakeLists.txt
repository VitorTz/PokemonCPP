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
add_executable (PokemonC "src/main.c" "src/constants.h" "src/util/types.h" "src/util/vector.h" "src/util/vector.c" "src/util/hash.h" "src/util/hash.c"   "src/util/set.h" "src/util/set.c" "src/util/util.h" "src/util/util.c" "src/util/map.h" "src/util/map.c" "src/util/texture_pool.h" "src/util/texture_pool.c" "src/ecs/entity_manager.h" "src/ecs/entity_manager.c" "src/ecs/component_manager.h" "src/ecs/components.h" "src/ecs/component_manager.c" "src/ecs/system_manager.h" "src/ecs/system.h" "src/ecs/system_manager.c" "src/ecs/ecs.h" "src/ecs/ecs.c" "src/ecs/components.c" "src/util/camera.h" "src/util/camera.c" "src/ecs/ecs_manager.h" "src/ecs/ecs_manager.c" "src/scene/scene.h" "src/scene/scene.c")


add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)