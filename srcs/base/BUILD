package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "base",
    hdrs = [
        "check.h",
        "stl_utils.h",
    ],
)

cc_test(
    name = "stl_utils_test",
    srcs = ["stl_utils_test.cpp"],
    deps = [
        ":base",
        "//test",
    ],
)
