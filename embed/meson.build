embed_srcs = [
  files('embed.c'),
]
embed_include_dirs = [
  inc,
  include_directories('./'),
  include_directories('../embed'),
]
embed_deps = [
  embed_utils_dep,
  cargs_dep,
  ansi_codes_dep,
]

if get_option('enable-binaries')
  embed_exec = executable('embed',
     embed_srcs,
     dependencies: embed_deps,
     pie: true,
     install: true,
     include_directories: embed_include_dirs,
  )
  if get_option('enable-binaries')
    test('embed', embed_exec, args: [])
  endif
endif
