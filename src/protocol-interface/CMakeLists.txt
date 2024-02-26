# This needs to be run as an external project. Don't call add_subdirectory on me... unless gRPC is installed on your machine.
find_package(gRPC CONFIG REQUIRED)

add_library(protocol-interface
  OBJECT
    "${CMAKE_CURRENT_LIST_DIR}/proto/helloworld.proto"
)

target_link_libraries(protocol-interface
  PUBLIC
    protobuf::libprotobuf gRPC::grpc++
)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto")

target_include_directories(protocol-interface PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
    TARGET protocol-interface
    OUT_VAR PROTO_GENERATED_FILES
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

set_source_files_properties(${PROTO_GENERATED_FILES} PROPERTIES SKIP_UNITY_BUILD_INCLUSION on)

protobuf_generate(
    TARGET protocol-interface
    OUT_VAR PROTO_GENERATED_FILES
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

set_source_files_properties(${PROTO_GENERATED_FILES} PROPERTIES SKIP_UNITY_BUILD_INCLUSION on)