package(
    default_visibility = ["//visibility:public"],
)

cc_binary(
    name = "flang",
    srcs = [
        "main.cpp",
    ],
    linkopts = [
        "-lboost_system",
        "-llog4cxx",
    ],
    deps = [
        "//front_end:flang_parser",
        "//front_end:flang_scanner",
        "//exception:exception",
        "//syntax_tree:syntax_tree",
    ]
)
