embed_test_srcs = [
  'embed-test.c',
]
embed_include_dirs = [
  include_directories('./'),
  include_directories('../embed-utils'),
  inc,
]
embed_test_deps = [
  embed_utils_dep,
]

if get_option('enable-binaries')
  embed_test_exec = executable('embed-test',
     [
      embed_test_srcs,
     ],
     dependencies: embed_test_deps,
     include_directories: [
       embed_include_dirs,
       inc,
     ],
  )
  if get_option('enable-binary-tests')
    test('embed-test', passh_program, args: [embed_test_exec, '-v','-a'])
  endif
endif
