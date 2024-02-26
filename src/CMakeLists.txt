include(ExternalProject)

# Ordering probably matters?

add_subdirectory(grpc-imported)

# Small "hack" to avoid CMake complaining about in-tree changes. This is ok. Maybe?
set(CMAKE_DISABLE_SOURCE_CHANGES OFF)
set(CMAKE_DISABLE_IN_SOURCE_BUILD OFF)
ExternalProject_Add(protocol-interface
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protocol-interface
  STEP_TARGETS build
  DEPENDS gRPC
)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

add_subdirectory(protocol)


# Does not depend on gRPC nor Protobuf
add_subdirectory(logic-virus)
