gen_rule(
  name = 'flang_scanner',
  cmd = 'flex --c++ -o $BUILD_DIR/flang_scanner.cpp flang_scanner.l',
  outs = ['flang_scanner.cpp'],
)

gen_rule(
  name = 'flang_parser',
  cmd = 'bison -L c++ --defines=$BUILD_DIR/flang_parser.h -o $BUILD_DIR/flang_parser.cpp flang_parser.y',
  outs = [
      'flang_parser.h',
      'flang_parser.cpp',
      'stack.hh',
  ],
)
