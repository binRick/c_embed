project('c_embed',
  ['c'],
  version : '0.0.1',
  default_options : [
    'warning_level=0',
    'c_std=gnu99',
  ]
)
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
#//***********************************************************/
deps = []
bin_srcs = []
cc = meson.get_compiler('c')
#//***********************************************************/
sh = find_program('sh', required : true)
pwd_bin = find_program('pwd', required : true)
#//***********************************************************/
pwd = run_command(pwd_bin, check: true).stdout().strip()
#//***********************************************************/
inc = include_directories(
  '.',
  './include', 
  './src', 
  './deps', 
  './deps/timestamp', 
  './deps/clibs/module', 
  './deps/slug', 
  './deps/bytes', 
  './submodules',
)
#//***********************************************************/
enabled_bins = [
  'c_embed',
]
bins = []
foreach bin : enabled_bins
        bin_src = [
          'src/' + bin + '.c',
          'deps/timestamp/timestamp.c',
          'src/uuid4.c',
        ]
        bins += {
          'name': bin,
          'executable': executable(bin, 
            [ 
              bin_src,
              files(bin_srcs),
            ],
            dependencies: [
              deps, 
            ],
            include_directories: [
              inc,
            ],
          )
        }
endforeach
if get_option('enable-binary-tests')
    foreach b : bins
      test(b['name'], b['executable'], args: ['--test'])
    endforeach
endif
#//***********************************************************/
