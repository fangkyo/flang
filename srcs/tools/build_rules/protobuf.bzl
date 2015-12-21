
def _impl(ctx):
  outputs = ctx.outputs.outs
  srcs = []
  srcs += ctx.files.srcs
  for dep in ctx.attr.deps:
    srcs += dep.proto.srcs
  
  srcs_path = " ".join([src.path for src in ctx.files.srcs])
  ctx.action(
      inputs=srcs,
      outputs=outputs,
      command="protoc -I. --cpp_out=%s %s" %  (ctx.var["GENDIR"], srcs_path))
  return struct(
    proto = struct(
      srcs = srcs 
    ),
  )
  

def _get_proto_outputs(srcs):
  res = []
  for src in srcs:
    cc_hdr = src[:-len(".proto")] + ".pb.h"
    cc_src = src[:-len(".proto")] + ".pb.cc"
    res.append(cc_hdr)
    res.append(cc_src)
  return res

proto_filetype = FileType([".proto"])

gen_proto = rule(
    implementation=_impl,
    attrs={
        "srcs": attr.label_list(allow_files=proto_filetype, mandatory=True),
        "deps": attr.label_list(providers=["proto"]),
        "outs": attr.output_list(mandatory=True, non_empty=True)
    },
    output_to_genfiles=True,
)

def cc_proto_library(name, srcs, deps=[], visibility=None):
  outs = _get_proto_outputs(srcs)
  proto_pkg = gen_proto(
      name=name + "_genproto",
      srcs=srcs,
      outs=outs,
      deps=[d + "_genproto" for d in deps])
  native.cc_library(
      name=name,
      srcs=[proto_pkg.label()],
      hdrs=[proto_pkg.label()],
      linkopts=["-lprotobuf"],
      deps = deps,
      visibility=visibility,
  )
