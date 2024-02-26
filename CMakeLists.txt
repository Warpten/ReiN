cmake_minimum_required(VERSION 3.28)

# add this options before PROJECT keyword
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(ReiN CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)

# set macro-directory
list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/cmake/macros")

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)
include(ConfigureScripts)

include(ConfigureBaseTargets)
include(CheckPlatform)

include(GroupSources)
include(AutoCollect)

add_subdirectory(dep)
add_subdirectory(submodules)
add_subdirectory(src)