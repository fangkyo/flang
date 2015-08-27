cc_library(
    name = "symbol",
    srcs = [
        "scope.cpp",
        "symbol.cpp",
        "data_type.cpp"
    ],
    deps = [
        "#boost_system",
    ]
)

cc_library(
    name = "symbol_table",
    srcs = [
        "symbol_table.cpp"
    ],
    deps = [
        "#boost_system",
        "#log4cxx",
        ":symbol",
    ]
)

cc_test(
    name = "scope_test",
    srcs = [
        "scope_test.cpp",
    ],
    deps = [
        ":symbol"
    ],
)

cc_test(
    name = "symbol_test",
    srcs = [
        "symbol_test.cpp",
    ],
    deps = [
        ":symbol",
    ]
)

cc_test(
    name = "symbol_table_test",
    srcs = ["symbol_table_test.cpp"],
    deps = [
        "#gtest_main",
        ":symbol_table",
    ]
)
