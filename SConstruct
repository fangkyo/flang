
lex_file = "etc/tinyc.l"
lex_cpp  = "src/tinyc_lex.cpp" 
lex_h    = "include/tinyc_lex.h"
lex_cmd  = "flex --header-file=" + lex_h + " -o " + lex_cpp + " " + lex_file

yacc_file = "etc/tinyc.y"
yacc_cpp  = "src/tinyc_yacc.cpp"
yacc_h    = "include/tinyc_yacc.h"
yacc_cmd  = "bison --defines=" + yacc_h + " -o " + yacc_cpp + " " + yacc_file  

lex = Command( [lex_cpp, lex_h], lex_file, lex_cmd )

yacc = Command( [yacc_cpp, yacc_h], yacc_file, yacc_cmd )

src_files = Glob( "src/*.cpp" )
objs = Object( src_files, CPPPATH="include", CCFLAGS="-std=c++11", LIBS="log4cxx" );

fun = Program( "fun", objs, CPPPATH="include", CCFLAGS="-std=c++11", LIBS="log4cxx" )

ftest=Program( "ftest", Glob("test/*.cpp")+ objs, CPPPATH="include",  CCFLAGS="-std=c++11", LIBS=["gtest","log4cxx"] )

Depends( fun, [lex, yacc] );

Default( fun ) 

