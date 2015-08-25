cc_library(
    name = "exception",
    srcs = [
        "exception.cpp",
    ],
    deps = [
        "#boost_system",
    ]
)

cc_test(
    name = "exception_test",
    srcs = [
        "exception_test.cpp"
    ],
    deps = [
        "#gtest_main",
        ":exception",
    ]
)
