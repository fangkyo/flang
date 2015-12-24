package(
		default_visibility = ["//visibility:public"],
)

cc_library(
    name = "test",
    srcs = ["test.cpp"],
    hdrs = ["test.h"],
    linkopts = [
        "-lgtest",
        "-lgtest_main",
        "-lpthread",
        "-llog4cxx",
    ],
)

cc_test(
    name = "backtrace_test",
    srcs = ["backtrace_test.cpp"],
    linkopts = [
        "-lbacktrace",
    ]
)
