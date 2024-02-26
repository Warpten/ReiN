CollectSourceFiles(
  ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE_SOURCES
  # Exclude
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(protocol STATIC ${PRIVATE_SOURCES})

find_package(protocol_interface)

target_link_libraries(protocol protocol-interface)