CollectSourceFiles(
  ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE_SOURCES
  # Exclude
)

GroupSources(${CMAKE_CURRENT_SOURCE_DIR})

add_library(logic_virus
  STATIC
    ${PRIVATE_SOURCES}
)

target_include_directories(logic_virus
  PUBLIC
    # Provide the binary dir for all child targets
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(logic_virus
  boost
  libassert
  compile-option-interface
  feature-interface
)

target_link_libraries(logic_virus
  PUBLIC
    boost
    libassert
    compile-option-interface
    feature-interface
)
