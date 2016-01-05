cc_library (
    name = "type_checker",
    srcs = [
        "type_checker.cpp",
    ],
    hdrs = ["type_checker.h"],
    linkopts = [
        "-lboost_system",
        "-llog4cxx",
    ],
    deps = [
        ":exception",
        "//symbol_table",
        "//syntax_tree:ast_node",
    ]
)

cc_library(
    name = "exception",
    srcs = [
        "exception.cpp",
    ],
    hdrs = ["exception.h"],
    linkopts = [
        "-lboost_system",
    ],
    deps = [
        "//exception:exception",
        "//symbol_table:symbol_table",
        "//syntax_tree:syntax_tree",
    ]
)
