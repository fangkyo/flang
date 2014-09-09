
def generate_lex(source, target, env, for_signature):
  return 'flex --header-file=%s -o %s %s' % (target[0], target[1], source[0])
lex = Builder(generator=generate_lex)

def generate_yacc(source, target, env, for_signature):
  return 'bison --defines=%s -o %s %s' % (target[0], target[1], source[0])
yacc = Builder(generator = generate_yacc)

env = Environment(BUILDERS={'Lex': lex, 'Yacc' : yacc})
env.Replace(CCFLAGS="-std=c++0x", CPPPATH="src")
env.Replace(LIBS=["log4cxx"])
env.Replace(LIBPATH=".")

lex_file = "etc/fun_lang.l"
lex_cpp  = "etc/fun_lang_lex.cpp"
lex_h    = "include/fun_lang_lex.h"
lex_h, lex_cpp = env.Lex(target=[lex_h,lex_cpp], source=lex_file)

yacc_file = "etc/fun_lang.y"
yacc_cpp  = "etc/fun_lang_yacc.cpp"
yacc_h    = "include/fun_lang_yacc.h"
yacc_h, yacc_cpp = env.Yacc(target=[yacc_h, yacc_cpp], source=yacc_file)

srcs = Glob("src/*.cpp")
lex_obj = env.Object(lex_cpp)
yacc_obj = env.Object(yacc_cpp)

synax_tree_lib = env.Lib("src/synax_tree/*.cpp")

objs = env.Object(srcs)
objs.append(lex_obj)
objs.append(yacc_obj)

obj_map = {}
for obj in objs:
  obj_map[str(obj)] = obj

flang = env.Program("flang", objs)
Default( flang )

