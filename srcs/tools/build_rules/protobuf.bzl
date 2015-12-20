# -*- mode: python; -*- PYTHON-PREPROCESSING-REQUIRED

def _GenDir(ctx):
  if not ctx.attr.includes:
    return ""
  if not ctx.attr.includes[0]:
    return ctx.label.package
  if not ctx.label.package:
    return ctx.attr.includes[0]
  return ctx.label.package + '/' + ctx.attr.includes[0]

def _CcOuts(srcs):
  return [s[:-len(".proto")] +  ".pb.h" for s in srcs] + \
         [s[:-len(".proto")] + ".pb.cc" for s in srcs]

def _PyOuts(srcs):
  return [s[:-len(".proto")] + "_pb2.py" for s in srcs]

def _proto_gen_impl(ctx):
  """General implementation for generating protos"""
  srcs = ctx.files.srcs
  deps = []
  deps += ctx.files.srcs
  gen_dir = "."
  import_flags = ["-I."]

  for dep in ctx.attr.deps:
    import_flags += dep.proto.import_flags
    deps += dep.proto.deps

  args = []
  if ctx.attr.gen_cc:
    args += ["--cpp_out=" + ctx.var["GENDIR"] + "/" + gen_dir]
  if ctx.attr.gen_py:
    args += ["--python_out=" + ctx.var["GENDIR"] + "/" + gen_dir]

  arguments = args + import_flags + [s.path for s in srcs]

  arguments = " ".join(arguments)
  if args:
    ctx.action(
        inputs=srcs + deps,
        outputs=ctx.outputs.outs,
        command = "protoc " + arguments
    )

  return struct(
      proto=struct(
          srcs=srcs,
          import_flags=import_flags,
          deps=deps,
      ),
  )

_proto_gen = rule(
    attrs = {
        "srcs": attr.label_list(allow_files = True),
        "deps": attr.label_list(providers = ["proto"]),
        "gen_cc": attr.bool(),
        "gen_py": attr.bool(),
        "outs": attr.output_list(),
    },
    output_to_genfiles = True,
    implementation = _proto_gen_impl,
)

def cc_proto_library(
        name,
        srcs=[],
        deps=[],
        **kargs):
  """Bazel rule to create a C++ protobuf library from proto source files

  NOTE: the rule is only an internal workaround to generate protos. The
  interface may change and the rule may be removed when bazel has introduced
  the native rule.

  Args:
    name: the name of the cc_proto_library.
    srcs: the .proto files of the cc_proto_library.
    deps: a list of dependency labels; must be cc_proto_library.
    include: a string indicating the include path of the .proto files.
    internal_bootstrap_hack: a flag indicate the cc_proto_library is used only
        for bootstraping. When it is set to True, no files will be generated.
        The rule will simply be a provider for .proto files, so that other
        cc_proto_library can depend on it.
    **kargs: other keyword arguments that are passed to cc_library.

  """
  outs = _CcOuts(srcs)
  proto_pkg = _proto_gen(
      name=name + "_genproto",
      srcs=srcs,
      deps=[s + "_genproto" for s in deps],
      gen_cc=1,
      outs=outs,
      visibility=["//visibility:public"],
  )
  native.cc_library(
      name=name,
      srcs=[proto_pkg.label()],
      hdrs=[proto_pkg.label()],
      linkopts=["-lprotobuf"],
      deps=deps,
      **kargs)

def my_macro(name, srcs, hdrs, visibility=None):
  native.cc_library(
    name = name,
    srcs = srcs,
    hdrs = hdrs,
    visibility = visibility,
  )
