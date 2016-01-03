package(
    default_visibility = ["//visibility:public"],
)

load("/tools/build_rules/protobuf", "cc_proto_library")

cc_proto_library(
  name = "ast_node_proto",
  srcs = ["ast_node.proto"],
)

cc_library(
    name = "ast_node",
    srcs = [
        "ast_visitor.cpp",
        "program_node.cpp",
        "stmt_node.cpp",
        "binary_exp_node.cpp",
        "unary_exp_node.cpp",
        "assign_node.cpp",
        "block_node.cpp",
        "name_node.cpp",
        "class_node.cpp",
        "ctrl_node.cpp",
        "type_node.cpp",
        "func_node.cpp",
        "var_decl_node.cpp",
        "new_node.cpp",
        "print_node.cpp",
        "import_node.cpp",
        "field_access_node.cpp",
    ],
    hdrs = [
        "ast_node.h",
        "ast_node_all.h",
        "ast_visitor.h",
        "program_node.h",
        "stmt_node.h",
        "exp_node.h",
        "binary_exp_node.h",
        "unary_exp_node.h",
        "assign_node.h",
        "block_node.h",
        "name_node.h",
        "class_node.h",
        "ctrl_node.h",
        "type_node.h",
        "primitive_node.h",
        "func_node.h",
        "var_decl_node.h",
        "new_node.h",
        "print_node.h",
        "import_node.h",
        "field_access_node.h",
    ],
    linkopts = [
        "-lboost_system",
        "-llog4cxx",
    ],
    deps = [
        "//exception",
        "//base",
        "//symbol_table:symbol",
        ":ast_node_proto",
    ],
)

cc_library(
    name = "syntax_tree",
    srcs = ["syntax_tree.cpp"],
    hdrs = ["syntax_tree.h"],
    deps = [
        ":ast_node",
    ],
)

cc_test(
    name = "field_access_node_test",
    srcs = ["field_access_node_test.cpp"],
    deps = [
        ":ast_node",
        "//test",
    ]
)
