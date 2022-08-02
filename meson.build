project('c_embed', ['c'],default_options:['warning_level=0','c_std=gnu99'],
  subproject_dir: 'submodules/c_deps/subprojects',
  )
#############################################################
cc = meson.get_compiler('c')
pwd = meson.current_source_dir()
passh_program = find_program('passh', required : true)
c_deps_dir = join_paths(meson.current_source_dir(),'submodules/c_deps')
#//***********************************************************/
inc = [
  include_directories(
    'submodules/c_deps/submodules/c_ansi',
    'submodules/c_deps/submodules','submodules/c_deps',
  ),
  include_directories(
    'submodules',
    '.',
  ),
]
#############################################################################
subdir('submodules')
#//////////////////////////////////////////////////////////////////////
subdir('embed-utils')
subdir('embed')
#subdir('embed-test')
#//////////////////////////////////////////////////////////////////////
