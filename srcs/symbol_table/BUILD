proto_library(
  name = 'data_type_proto',
  srcs = ['data_type.proto'],
  deps = [
      '#protobuf',
  ]
)

proto_library(
  name = 'symbol_info_proto',
  srcs = ['symbol_info.proto'],
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
  name = 'data_type_entry',
  srcs = ['data_type_entry.cpp'],
  deps = [
      ':data_type_proto',
  ]
)

cc_library(
  name = 'function_entry',
  srcs = ['function_entry.cpp'],
  deps = [
      ':data_type_entry',
  ]
)
