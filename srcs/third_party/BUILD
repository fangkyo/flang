package(
    default_visibility = ["//visibility:public"],
)

licenses(["notice"])

cc_library(
    name = "backward_cpp",
    # hdrs = ["//third_party/backward-cpp:backward.hpp"],
    hdrs = ["backward-cpp/backward.hpp"],
    defines = ["BACKWARD_HAS_BFD=1"],
    linkopts = [
        "-lbfd",
        "-ldl",
    ],
)
