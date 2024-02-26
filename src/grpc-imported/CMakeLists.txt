include(ExternalProject)

# ########################################### #
#  Setup for gRPC CMake hell.                 #
# ########################################### #

ExternalProject_Add(gRPC
  GIT_REPOSITORY git@github.com:grpc/grpc.git
  # PREFIX ${CMAKE_CURRENT_BINARY_DIR}/grpc
  GIT_SHALLOW TRUE
  STEP_TARGETS build
  CMAKE_ARGS
    # https://github.com/protocolbuffers/protobuf/issues/12185
    -DABSL_ENABLE_INSTALL=ON
    -DABSL_BUILD_TESTING=OFF
    -DABSL_BUILD_TEST_HELPERS=OFF
    # A future Abseil release will default ABSL_PROPAGATE_CXX_STD to ON for CMake
    # 3.8 and up.  We recommend enabling this option to ensure your project still
    # builds correctly.
    -DABSL_PROPAGATE_CXX_STD=ON
    -DgRPC_INSTALL=ON
    -DgRPC_BUILD_TESTS=OFF
    -DgRPC_BUILD_CODEGEN=ON
    -DgRPC_BUILD_GRPC_CPP_PLUGIN=ON
    -DgRPC_BUILD_CSHARP_EXT=OFF
    -DgRPC_BUILD_GRPC_CSHARP_PLUGIN=OFF
    -DgRPC_BUILD_GRPC_NODE_PLUGIN=OFF
    -DgRPC_BUILD_GRPC_OBJECTIVE_C_PLUGIN=OFF
    -DgRPC_BUILD_GRPC_PHP_PLUGIN=OFF
    -DgRPC_BUILD_GRPC_PYTHON_PLUGIN=OFF
    -DgRPC_BUILD_GRPC_RUBY_PLUGIN=OFF
    -Dprotobuf_INSTALL=ON
    -Dprotobuf_BUILD_TESTS=OFF
    -Dprotobuf_BUILD_CONFORMANCE=OFF
    -Dprotobuf_BUILD_EXAMPLES=OFF
    -Dprotobuf_BUILD_PROTOC_BINARIES=OFF
    -Dprotobuf_DISABLE_RTTI=OFF
    -Dprotobuf_MSVC_STATIC_RUNTIME=OFF
)

add_library(grpc-imported STATIC IMPORTED GLOBAL)

add_dependencies(grpc-imported gRPC)

# find_package(gRPC CONFIG REQUIRED)

# add_library(protocol
#   OBJECT
#     # All .proto files
#     "${CMAKE_CURRENT_SOURCE_DIR}/shared.proto"
#     "${CMAKE_CURRENT_SOURCE_DIR}/ClientServices.proto"
#     "${CMAKE_CURRENT_SOURCE_DIR}/ServerServices.proto"
# )
# 
# target_link_libraries(protocol
#   PUBLIC
#     protobuf::libprotobuf
#     gRPC::grpc++_unsecure
# )
# 
# set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
# set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}")
# 
# list(APPEND CMAKE_MODULE_PATH
#   "${gRPC_SOURCE_DIR}/cmake"
#   "${gRPC_SOURCE_DIR}/third_party/protobuf/cmake")
# 
# protobuf_generate(
#     TARGET protocol
#     OUT_VAR PROTO_GENERATED_FILES
#     IMPORT_DIRS ${PROTO_IMPORT_DIRS}
#     PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
# )
# set_source_files_properties(${PROTO_GENERATED_FILES} PROPERTIES SKIP_UNITY_BUILD_INCLUSION on)
# 
# protobuf_generate(
#     TARGET protocol
#     OUT_VAR PROTO_GENERATED_FILES
#     LANGUAGE grpc
#     GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
#     PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
#     # PLUGIN_OPTIONS "generate_mock_code=true"
#     IMPORT_DIRS ${PROTO_IMPORT_DIRS}
#     PROTOC_OUT_DIR "${PROTO_BINARY_DIR}"
# )
# set_source_files_properties(${PROTO_GENERATED_FILES} PROPERTIES SKIP_UNITY_BUILD_INCLUSION on)
# 
# target_include_directories(protocol PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")
