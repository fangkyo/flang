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
        "binary_exp_node.cpp",
        "unary_exp_node.cpp",
        "assign_node.cpp",
        "block_node.cpp",
        "name_node.cpp",
        "class_node.cpp",
        "ctrl_node.cpp",
        "type_node.cpp",
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
    ],
    linkopts = [
        "-lboost_system"
    ],
    deps = [
        "//exception",
        "//base",
        "//symbol_table:symbol",
        ":ast_node_proto",
    ],
)

#cc_library(
#		name = "ast_node",
#		hdrs = glob(["*_node.h"]),
#		srcs = glob(["*_node.cpp"]),
#		deps = [
#			":ast_visitor",
#			"//symbol_table:symbol",
#		],
#)


cc_library(
    name = "syntax_tree",
    srcs = [
        "syntax_tree.cpp",
    ],
    hdrs = ["syntax_tree.h"],
    deps = [
        ":ast_node",
    ],
)

cc_library(
    name = "program_node",
    srcs = [
        "program_node.cpp",
    ],
    hdrs = ["program_node.h"],
    linkopts = ["-lboost_system"],
    deps = ["//base"],
)

cc_library(
    name = "block_node",
    srcs = [
        "block_node.cpp",
    ],
    hdrs = ["block_node.h"],
    linkopts = ["-lboost_system"],
    deps = ["//base"],
)

cc_library(
    name = "print_node",
    srcs = [
        "print_node.cpp",
    ],
    hdrs = ["print_node.h"],
)

cc_library(
    name = "unary_exp_node",
    srcs = [
        "unary_exp_node.cpp",
    ],
    hdrs = ["unary_exp_node.h"],
)

cc_library(
    name = "binary_exp_node",
    srcs = [
        "binary_exp_node.cpp",
    ],
    hdrs = ["binary_exp_node.h"],
    deps = ["//base"],
)

cc_library(
    name = "assign_node",
    srcs = [
        "assign_node.cpp",
    ],
    hdrs = ["assign_node.h"],
    deps = [":exp_node"],
)

cc_library(
    name = "name_node",
    srcs = [
        "name_node.cpp",
    ],
    hdrs = ["name_node.h"],
    linkopts = ["-lboost_system"],
)

cc_library(
    name = "ctrl_node",
    srcs = [
        "ctrl_node.cpp",
    ],
    hdrs = ["ctrl_node.h"],
)

cc_library(
    name = "new_node",
    srcs = [
        "new_node.cpp",
    ],
    hdrs = ["new_node.h"],
)

cc_library(
    name = "var_decl_node",
    srcs = [
        "var_decl_node.cpp",
    ],
    hdrs = ["var_decl_node.h"],
    linkopts = ["-lboost_system"],
    deps = [
        ":data_type_node",
    ],
)

cc_library(
    name = "data_type_node",
    srcs = [
        "data_type_node.cpp",
    ],
    hdrs = [
        "data_type_node.h",
    ],
    deps = [":ast_node"],
)

cc_library(
    name = "func_node",
    srcs = [
        "func_node.cpp",
    ],
    hdrs = ["func_node.h"],
    linkopts = ["-lboost_system"],
    deps = [
        ":var_decl_node",
    ],
)

cc_library(
    name = "class_node",
    srcs = [
        "class_node.cpp",
    ],
    hdrs = ["class_node.h"],
    linkopts = ["-lboost_system"],
    deps = [
        ":func_node",
        ":name_node",
        ":var_decl_node",
    ],
)

cc_library(
    name = "reference_node",
    srcs = [
        "reference_node.cpp",
    ],
    hdrs = ["reference_node.h"],
    linkopts = ["-lboost_system"],
    deps = [
        ":ast_visitor",
    ],
)
