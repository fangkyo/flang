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
		linkopts = ["-lboost_system"],
		data = [
				"//front_end:flang_parser_src",
		],
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
