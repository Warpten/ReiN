# Derived from libassert's CMakeLists (submodules/libassert/CMakeLists.txt), excluding tests and install targets

option(ASSERT_DECOMPOSE_BINARY_LOGICAL "Enables expression decomposition of && and ||" OFF)
option(ASSERT_LOWERCASE "Enables assert alias for ASSERT" OFF)
option(ASSERT_USE_MAGIC_ENUM "Use the MagicEnum library to print better diagnostics for enum classes" ON)
set(ASSERT_FAIL "" CACHE STRING "ASSERT_FAIL")

add_library(libassert
  STATIC
    ${CMAKE_SOURCE_DIR}/submodules/libassert/src/assert.cpp)

target_include_directories(libassert
  PUBLIC
    ${CMAKE_SOURCE_DIR}/submodules/libassert/include/
)

target_compile_features(libassert
  PUBLIC
    cxx_std_17
)

# libassert uses relocs, -fpic has to be used to allow shared libs to link libassert as a static library.
# changed from (set(CMAKE_POSITION_INDEPENDANT_CODE ON) to avoid poisining
set_property(TARGET libassert 
  PROPERTY POSITION_INDEPENDANT_CODE ON
)

set_target_properties(libassert
  PROPERTIES
    CXX_STANDARD_REQUIRED TRUE
    CXX_EXTENSIONS OFF
)

target_compile_options(libassert
  PRIVATE
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror=return-type -Wshadow>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX /permissive- /wd4005>
)

target_link_libraries(libassert
  PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:dbghelp>
    ${CMAKE_DL_LIBS}
)

if(ASSERT_DECOMPOSE_BINARY_LOGICAL)
  target_compile_definitions(libassert PUBLIC ASSERT_DECOMPOSE_BINARY_LOGICAL)
endif()

if(ASSERT_LOWERCASE)
  target_compile_definitions(libassert PUBLIC ASSERT_LOWERCASE)
endif()

if(ASSERT_USE_MAGIC_ENUM)
  target_compile_definitions(libassert PUBLIC ASSERT_USE_MAGIC_ENUM)
endif()

if(NOT "${ASSERT_FAIL}" STREQUAL "")
  target_compile_definitions(libassert PUBLIC ASSERT_FAIL=${ASSERT_FAIL})
endif()


if(CMAKE_BUILD_TYPE STREQUAL "")
  message(FATAL_ERROR "Setting CMAKE_BUILD_TYPE is required")
endif()
