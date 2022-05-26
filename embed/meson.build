project('embeds', ['c'],
  default_options: [
   'warning_level=0',
   'c_std=gnu99',
  ]
)
embeds_bins = [
  'embed',
]
config = configuration_data()
version = run_command('git', 'describe', '--tags')
config.set('version', version.stdout().strip())
add_project_arguments('-D_GNU_SOURCE', language : 'c')
add_project_arguments('-DDBG_H_DEF_ONCE', language : 'c')
add_project_arguments('-DDBG_H_NO_WARNING', language : 'c')
add_project_arguments('-DASSERTF_DEF_ONCE', language : 'c')
add_project_arguments('-DLOG_USE_COLOR', language : 'c')
add_project_arguments('-DLOG_LEVEL=TRACE', language : 'c')
add_project_arguments('-Wno-pragma-once-outside-header', language : 'c')
add_project_arguments('-Wno-incompatible-pointer-types', language : 'c')
add_project_arguments('-Wno-pointer-sign', language : 'c')
#//***********************************************************/
deps = []
bin_srcs = [
  'deps/timestamp/timestamp.c',
  'vendor/uuid4/uuid4.c',
]
cc = meson.get_compiler('c')
#//***********************************************************/
sh = find_program('sh', required : true)
pwd_bin = find_program('pwd', required : true)
#//***********************************************************/
pwd = run_command(pwd_bin, check: true).stdout().strip()
#//***********************************************************/
#//***********************************************************/
inc = include_directories(
  '.',
  './include', 
  './src', 
  './vendor', 
  './deps', 
  './deps/timestamp', 
  './deps/clibs/module', 
  './deps/slug', 
  './deps/bytes', 
  './submodules/djbhash/src',
  './submodules',
)
#//***********************************************************/
subdir('meson/deps/cstringfn')
if get_option('enable-binaries')
 foreach b : embeds_bins
  bin_src = [
    'src/' + b + '.c',
  ]
  bin = {
          'name': b,
          'executable': executable(b, 
            [ 
              bin_src,
              files(bin_srcs),
            ],
            dependencies: [
              deps, 
              cstringfn_dep,
            ],
            include_directories: [
              inc,
            ],
          )
  }
  if get_option('enable-binary-tests')
    test(bin['name'], bin['executable'], args: ['--test'])
  endif
 endforeach
endif
