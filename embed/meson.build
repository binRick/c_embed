embed_srcs = [
  'embed.c',
]
embed_include_dirs = [
  include_directories('./'),
  include_directories('../embed'),
  inc,
]
embed_deps = [
  embed_utils_dep,
]

if get_option('enable-binaries')
  embed_exec = executable('embed',
     [
      embed_srcs,
     ],
     dependencies: embed_deps,
     include_directories: [
       embed_include_dirs,
       inc,
     ],
  )
  if get_option('enable-binaries')
    test('embed', embed_exec, args: [])
  endif
endif
