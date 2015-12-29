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
    deps = [
        "//base",
    ],
)
