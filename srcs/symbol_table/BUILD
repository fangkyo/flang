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
  name = 'symbol_info',
  srcs = ['symbol_info.cpp'],
  deps = [
    '#boost_system',
    ':symbol_info_proto',
  ]
)

cc_library(
  name = 'scope',
  srcs = ['scope.cpp'],
  deps = [
      '#boost_system',
      '#log4cxx',
      ':symbol_info',
  ]
)
