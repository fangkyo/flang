
def generate_lex(source, target, env, for_signature):
  assert len(target) > 0
  if len(target) == 1:
    return "flex -c++ -o %s %s" % (target[0], source[0])
  else:
    return "flex --c++ --header-file=%s -o %s %s" % (target[0], target[1], source[0])

lex = Builder(generator=generate_lex)

def generate_yacc(source, target, env, for_signature):
  return "bison -L c++ --defines=%s -o %s %s" % (target[0], target[1], source[0])
yacc = Builder(generator = generate_yacc)

env = Environment(BUILDERS={"Lex": lex, "Yacc" : yacc})
env.Replace(CCFLAGS="-std=c++11", CPPPATH=["#build", "#srcs"])
env.Replace(LIBS=["log4cxx",])
env.Replace(LIBPATH="#build")

SConscript(
    ["srcs/SConscript"],
    exports = 'env',
    variant_dir = 'build',
    duplicate = 0
)
