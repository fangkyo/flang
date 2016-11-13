load("//third_party/protobuf:protobuf.bzl", cc_proto_alias = "cc_proto_library")

def cc_proto_library(
        name,
        srcs=[],
        deps=[],
        cc_libs=[],
        include=None,
        protoc="//:protoc",
        internal_bootstrap_hack=False,
        use_grpc_plugin=False,
        default_runtime="//:protobuf",
        **kargs):
  cc_proto_alias(
      name=name,
      srcs=srcs,
      deps=deps,
      cc_libs=cc_libs,
      include=include,
      protoc="//third_party/protobuf:protoc",
      internal_bootstrap_hack=internal_bootstrap_hack,
      use_grpc_plugin=use_grpc_plugin,
      default_runtime="//third_party/protobuf:protobuf",
      **kargs)
