fs_lib = library('fs', 
'../../../vendor/fs/fs.c',
install: false, dependencies: [], 
  include_directories: [
'../../../vendor/fs',
  ]
)
fs_dep = declare_dependency(include_directories: [
'../../../vendor/fs',
  ], link_with: fs_lib)
#deps += b64_dep
