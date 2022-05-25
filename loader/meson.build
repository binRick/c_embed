project('loaders',
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
submodule_srcs = [
]
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
  './deps', 
  './submodules',
  './src', 
)
#//***********************************************************/
miniz_dep = dependency('miniz', fallback : [ 'miniz', 'miniz_dep'])
subdir('meson/deps/chan')
subdir('meson/deps/b64')
#chan_dep = dependency('chan', fallback : [ 'chan', 'chan_dep'])
#libuv_dep = dependency('libuv', fallback : [ 'libuv', 'libuv_dep'])
#//***********************************************************/
test_env = environment()
#//***********************************************************/
subdir('meson/deps/djbhash')
enabled_bins = [
  { 'bin': 'loader_list',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['list'],
                                            ],    
                                  }
                                 ],    
  },
  { 'bin': 'loader_chan',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['chan'],
                                            ],    
                                  }
                                 ],    
  },
  { 'bin': 'loader_iterate',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['names'],
                                             ['sizes'],
                                            ],    
                                  }
                                 ],    
  },
  { 'bin': 'loader_stats',   'tests': [
                                  { 
                                    'args': [
                                             ['--test'],
                                             ['size'],
                                             ['qty'],
                                             ['timestamp'],
                                            ],    
                                  }
                                 ],    
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
                                  }
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
     dependencies: [
      deps, 
      djbhash_dep, 
      chan_dep, 
      b64_dep, 
     ],
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
