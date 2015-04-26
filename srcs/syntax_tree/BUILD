cc_library(
 name = 'syntax_tree',
 srcs = [
   'syntax_tree.cpp',
  ],
 deps = [
   ':program_node',
   ':print_node',
   ':unary_exp_node',
   ':binary_exp_node',
   ':assign_node',
   ':name_node',
   ':var_declaration_node',
   ':func_node',
   ':class_node',
   ':data_type_node',
   ':new_node',
   ':ctrl_node',
   ':block_node',
 ]
)

cc_library(
  name = 'program_node',
  srcs = [
    'program_node.cpp',
  ],
  deps = [
    '#boost_system'
  ]
)

cc_library(
  name = 'block_node',
  srcs = [
    'block_node.cpp',
  ],
  deps = [
    '#boost_system'
  ]
)


cc_library(
  name = 'print_node',
  srcs = [
    'print_node.cpp',
  ]
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
)

cc_library(
  name = 'name_node',
  srcs = [
    'name_node.cpp'
  ],
  deps = [
    '#boost_system',
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
  name = 'var_declaration_node',
  srcs = [
    'var_declaration_node.cpp',
  ],
  deps = [
    '#boost_system',
    ':data_type_node',
  ]
)

cc_library(
  name = 'data_type_node',
  srcs = [
    'data_type_node.cpp'
  ]
)

cc_library(
  name = 'func_node',
  srcs = [
    'func_node.cpp'
  ],
  deps = [
    '#boost_system',
    ':var_declaration_node',
  ]
)

cc_library(
  name = 'class_node',
  srcs = [
    'class_node.cpp',
  ],
  deps = [
    '#boost_system',
    ':func_node',
    ':name_node',
    ':var_declaration_node',
  ]
)

