package(
    default_visibility = ["//visibility:public"],
)

load("/tools/build_rules/protobuf", "cc_proto_library")

cc_proto_library(
    name = "symbol_proto",
    srcs = ["symbol.proto"],
    deps = ["//syntax_tree:ast_node_proto"],
)

cc_library(
    name = "symbol",
    srcs = [
        "data_type.cpp",
        "scope.cpp",
        "symbol.cpp",
    ],
    hdrs = [
        "data_type.h",
        "scope.h",
        "symbol.h",
    ],
    linkopts = ["-lboost_system"],
    deps = ["//base"],
)

cc_library(
    name = "symbol_table",
    srcs = [
        "symbol_table.cpp",
    ],
    hdrs = ["symbol_table.h"],
    linkopts = [
        "-lboost_system",
        "-llog4cxx",
    ],
    deps = [
        ":symbol",
    ],
)

cc_test(
    name = "scope_test",
    srcs = [
        "scope_test.cpp",
    ],
    deps = [
        ":symbol",
    ],
)

cc_test(
    name = "symbol_test",
    srcs = [
        "symbol_test.cpp",
    ],
    deps = [
        ":symbol",
    ],
)

#cc_test(
#    name = "symbol_table_test",
#    srcs = ["symbol_table_test.cpp"],
#    deps = [
#        "#log4cxx",
#        "#gtest_main",
#        ":symbol_table",
#        "//test:test",
#    ]
#)
