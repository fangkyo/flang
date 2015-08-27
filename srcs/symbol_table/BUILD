cc_library(
    name = "scope",
    srcs = [
        "scope.cpp",
    ],
    deps = [
        "#boost_system",
    ]
)

cc_library(
    name = "symbol",
    srcs = [
        "symbol.cpp",
        "data_type.cpp"
    ],
    deps = [
        ":scope",
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
  name = "symbol_table_test",
  srcs = ["symbol_table_test.cpp"],
  deps = [
      "#gtest_main",
      ":symbol_table",
  ]
)
