gen_rule(
    name = "flang_scanner_src",
    cmd = "flex --c++ -o $BUILD_DIR/flang_scanner.cpp flang_scanner.l",
    outs = ["flang_scanner.cpp"],
)

gen_rule(
    name = "flang_parser_src",
    cmd = "bison -L c++ --defines=$BUILD_DIR/flang_parser.h -o $BUILD_DIR/flang_parser.cpp flang_parser.y",
    outs = [
        "flang_parser.h",
        "flang_parser.cpp",
        "stack.hh",
    ],
)

cc_library(
    name = "flang_scanner",
    srcs = ["flang_scanner.cpp"],
    deps = [
        ":flang_parser_src",
        ":flang_scanner_src",
        "//exception:exception",
    ]
)

cc_library(
    name = "flang_parser",
    srcs = ["flang_parser.cpp"],
    deps = [
        ":flang_parser_src",
        ":flang_scanner",
    ]
)

cc_test(
    name = "flang_scanner_test",
    srcs = ["flang_scanner_test.cpp"],
    deps = [
        ":flang_scanner",
        "//test:test",
    ]
)

cc_binary(
    name = "flang",
    srcs = [
        "main.cpp",
        "flang_parser.cpp",
        "flang_scanner.cpp",
    ],
    deps = [
        "#boost_system",
        "#log4cxx",
        ":flang_parser",
        ":flang_scanner",
        "//exception:exception",
        "//syntax_tree:syntax_tree",
    ]
)
