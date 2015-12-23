package(
    default_visibility = ["//visibility:public"],
)

genrule(
    name = "flang_scanner_src",
    srcs = ["flang_scanner.l"],
    outs = ["flang_scanner.cpp"],
    cmd = "flex --c++ -o $@ $(location flang_scanner.l)",
)

genrule(
    name = "flang_parser_src",
    srcs = ["flang_parser.y"],
    outs = [
        "flang_parser.h",
        "flang_parser.cpp",
        "location.hh",
        "position.hh",
        "stack.hh",
    ],
    cmd = "bison -L c++ --defines=$(location flang_parser.h) -o $(location flang_parser.cpp) $(location flang_parser.y)",
)

cc_library(
    name = "flang_scanner",
    srcs = ["flang_scanner.cpp"],
    hdrs = [
        "flang_parser.h",
        "flang_scanner.h",
        "location.hh",
        "position.hh",
        "stack.hh",
    ],
    copts = [
        "-Wno-sign-compare",
    ],
    data = [
        ":flang_parser_src",
        ":flang_scanner_src",
    ],
    deps = [
        "//exception",
        "//syntax_tree",
    ],
)

cc_library(
    name = "flang_parser",
    srcs = ["flang_parser.cpp"],
    hdrs = ["flang_parser.h"],
    linkopts = [
        "-llog4cxx",
    ],
    copts = [
        "-Wno-sign-compare",
    ],
    deps = [
        ":flang_scanner",
        "//syntax_tree",
    ],
)

#cc_test(
#    name = "flang_scanner_test",
#    srcs = ["flang_scanner_test.cpp"],
#    deps = [
#        ":flang_scanner",
#        "//test:test",
#    ]
#)
