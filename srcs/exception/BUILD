package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "exception",
    srcs = ["exception.cpp"],
    hdrs = [
        "exception.h",
        "//front_end:location.hh",
        "//front_end:position.hh",
    ],
    data = [
        "//front_end:flang_parser_src",
    ],
    linkopts = ["-lboost_system"],
    deps = [
        "//base",
    ],
)

cc_library(
    name = "exception_manager",
    srcs = ["exception_manager.cpp"],
    hdrs = ["exception_manager.h"],
    linkopts = ["-lboost_system"],
    deps = [
        ":exception",
    ]
)

#cc_test(
#    name = "exception_test",
#    srcs = [
#        "exception_test.cpp"
#    ],
#    deps = [
#        "#gtest_main",
#        ":exception",
#    ]
#)
