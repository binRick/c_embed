embed_utils_srcs = [
  'embed-utils.c',
]
embed_utils_inc_dirs = [
  inc,
]
embed_utils_deps = [
  uuid4_dep,
  timestamp_dep,
  bytes_dep,
  ms_dep,
  c_fsio_dep, 
  c_stringfn_dep,
  c_string_buffer_dep,
  slug_dep,
  djbhash_dep,
]

embed_utils_lib = static_library('embed-utils',
  embed_utils_srcs,
  install: true,
  dependencies: embed_utils_deps,
  include_directories: embed_utils_inc_dirs,
  c_args: [],
)

embed_utils_dep = declare_dependency(
  include_directories: embed_utils_inc_dirs,
  link_with: embed_utils_lib,
)
