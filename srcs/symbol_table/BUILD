proto_library(
  name = 'symbol_info_proto',
  srcs = ['symbol_info.proto'],
  deps = [
      '#protobuf',
  ]
)

proto_library(
  name = 'symbol_table_proto',
  srcs = ['symbol_table.proto'],
  deps = [
      '#protobuf',
  ]
)

cc_library(
  name = 'symbol_table',
  srcs = [
    'scope.cpp',
    'symbol_info.cpp',
    'symbol_table.cpp'
  ],
  deps = [
      '#boost_system',
      ':symbol_info_proto',
  ]
)

cc_test(
  name = 'symbol_table_test',
  srcs = ['symbol_table_test.cpp'],
  deps = [
      '#gtest_main',
      '#gtest',
      ':symbol_table',
  ]
)
