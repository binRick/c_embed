project(
  'loaders',
  ['c'],
version : '1.0.0',
default_options : ['warning_level=0', 'c_std=gnu99']
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
submodule_srcs = [
]
cc = meson.get_compiler('c')
#//***********************************************************/
sh = find_program('sh', required : true)
pwd_bin = find_program('pwd', required : true)
m_dep = cc.find_library('m', required : false)
#//***********************************************************/
pwd = run_command(pwd_bin, check: true).stdout().strip()
#//***********************************************************/
inc = include_directories(
  '.',
  './include', 
  './deps', 
  './submodules',
  './src', 
)
#//***********************************************************/
#//miniz_dep = dependency('miniz', fallback : [ 'miniz', 'miniz_dep'])
#termbox = dependency('termbox', fallback : [ 'termbox', 'termbox_dep'])
dep_cargs = dependency('cargs',fallback:['cargs', 'dep_cargs'])
spng_dep = dependency('libspng',fallback:['libspng', 'spng_dep'])
#dep_foxenunit = dependency('libfoxenunit',fallback:['libfoxenunit', 'dep_foxenunit'])
#dep_libtermkey = dependency('libtermkey',fallback:['libtermkey', 'dep_termkey'])
#termpaint_dep = dependency('termpaint',fallback:['libtermpaint','termpaint_dep'])
#,'libtermpaint', 'dep_libtermpaint'])
subdir('meson/deps')
#chan_dep = dependency('chan', fallback : [ 'chan', 'chan_dep'])
libuv_dep = dependency('libuv', fallback : [ 'libuv', 'libuv_dep'])
#//***********************************************************/
test_env = environment()
#//***********************************************************/
subdir('meson/deps/djbhash')
color0_srcs = [
    'src/color0/main.c',
    'src/color0/options.c',
    'src/color0/colors.c',
    'src/color0/output.c'
]
executable('color0', color0_srcs, dependencies: [m_dep], install: false)
enabled_bins = [
  #  { 'bin': 'termkey0',          'tests': [], 'deps': [dep_libtermkey], },
  { 'bin': 'spng0',             'tests': [], 'deps': [spng_dep], },
  { 'bin': 'cargs0',            'tests': [], 'deps': [dep_cargs], },
  #  { 'bin': 'vtparse0',          'tests': [], 'deps': [], },
  #{ 'bin': 'vtparse_example',   'tests': [], 'deps': [], },
  { 'bin': 'loader_list',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['list'],
                                            ],    
                                  }
                                 ],    
                                 'deps': [deps,djbhash_dep,chan_dep,b64_dep],
  },
  { 'bin': 'loader_chan',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['chan'],
                                            ],    
                                  }
                                 ],    
                                 'deps': [deps,djbhash_dep,chan_dep,b64_dep],
  },
  { 'bin': 'loader_iterate',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['names'],
                                             ['sizes'],
                                            ],    
                                  },
                                 ],    
                                  'deps': [deps,djbhash_dep,chan_dep,b64_dep],
  },
  { 'bin': 'loader_stats',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['size'],
                                             ['qty'],
                                             ['timestamp'],
                                            ],    
                                  },
                                 ],    
                                  'deps': [deps,djbhash_dep,chan_dep,b64_dep],
  },
  { 'bin': 'loader_hash',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['iterate'],
                                             ['json'],
                                             ['names'],
                                             ['sizes'],
                                            ],    
                                  },
                                 ],    
                                  'deps': [deps,djbhash_dep,chan_dep,b64_dep],
  },
  { 'bin': 'loader_dev',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                            ],    
                                  },
                                 ],    
                                 'deps': [
                                   deps,djbhash_dep,chan_dep,b64_dep,
                                   ],
  },
]
if get_option('enable-binaries')
  foreach b : enabled_bins
   bin_src = [
      'src/' + b['bin'] + '.c',
   ]
   e = {
    'name': b['bin'],
    'exec': executable(b['bin'], 
     [ 
      bin_src,
      files(bin_srcs),
      files(submodule_srcs),
     ],
     dependencies: b['deps'],
     include_directories: [
      inc,
     ],
    ),
   }
   if get_option('enable-binary-tests')
    foreach t: b['tests']
     foreach a: t['args']
      test(b['bin'], e['exec'], args: a, env: test_env)
     endforeach
    endforeach
   endif
  endforeach
endif
#//***********************************************************/
