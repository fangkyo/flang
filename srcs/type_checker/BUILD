cc_library (
    name = "type_checker",
    srcs = [
        "type_checker.cpp",
    ],
    deps = [
        "#boost_system",
        "#log4cxx",
        ":exception",
        "//symbol_table:symbol_table",
        "//syntax_tree:syntax_tree",
    ]
)

cc_library(
    name = "exception",
    srcs = [
        "exception.cpp",
    ],
    deps = [
        "#boost_system",
        "//exception:exception",
        "//symbol_table:symbol_table",
        "//syntax_tree:syntax_tree",
    ]
)
