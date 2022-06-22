project('c_embed', ['c'],default_options:['warning_level=0','c_std=gnu99'])
#############################################################
cc = meson.get_compiler('c')
pwd = meson.current_source_dir()
meson_deps_dir = join_paths(meson.current_source_dir(),'submodules/meson_deps')
#//***********************************************************/
inc = [
  include_directories(
    'submodules/meson_deps/submodules/c_ansi',
    'submodules/meson_deps/submodules','submodules/meson_deps',
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
subdir('embed-test')
#//////////////////////////////////////////////////////////////////////
