package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "base",
    hdrs = [
        "base.h",
        "check.h",
        "stl_utils.h",
    ],
    srcs = [
        "base.cpp",
    ],
    copts = ["-DBACKWARD_HAS_BFD=1"],
    deps = [
        "//third_party:backward_cpp",
    ]
)

cc_test(
    name = "stl_utils_test",
    srcs = ["stl_utils_test.cpp"],
    deps = [
        ":base",
        "//test",
    ],
)
