#cc_library(
#  name = 'syntax_tree',
#  srcs = [
#    'syntax_tree.cpp',
#       'class_node.cpp',
#       'data_type.cpp',
#       'print_node.cpp',
#       'ctrl_node.cpp',
#       'declare_node.cpp',
#       'func_node.cpp',
#       'exp_node.cpp',
#   ],
#  deps = [
#    ':program_node',
#  ]
#)

cc_library(
  name = 'program_node',
  srcs = [
    'program_node.cpp',
  ],
)

cc_library(
  name = 'unary_exp_node',
  srcs = [
    'unary_exp_node.cpp',
  ],
)

cc_library(
  name = 'binary_exp_node',
  srcs = [
    'binary_exp_node.cpp',
  ],
)

cc_library(
  name = 'assign_node',
  srcs = [
    'assign_node.cpp',
  ],
  deps = [
    ':var_node',
  ]
)

cc_library(
  name = 'var_node',
  srcs = [
    'var_node.cpp'
  ]
)

cc_library(
  name = 'ctrl_node',
  srcs = [
    'ctrl_node.cpp'
  ]
)

cc_library(
  name = 'new_node',
  srcs = [
    'new_node.cpp',
  ]
)

cc_library(
  name = 'declare_node',
  srcs = [
    'declare_node.cpp',
  ],
  deps = [
    '#boost_system'
  ]
)

cc_library(
  name = 'data_type_node',
  srcs = [
    'data_type_node.cpp'
  ]
)
