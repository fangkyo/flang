proto_library(
  name = 'data_type_proto',
  srcs = ['data_type.proto'],
  deps = [
      '#protobuf',
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
