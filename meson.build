project('c_embed', ['c'],default_options:['warning_level=0','c_std=gnu99'])
#############################################################
cc = meson.get_compiler('c')
pwd = meson.current_source_dir()
meson_deps_dir = join_paths(meson.current_source_dir(),'submodules/meson_deps')
#//***********************************************************/
inc = [
  include_directories(
    './',
  ),
]
#############################################################################
subdir('submodules/meson_deps/meson/args')
subdir('submodules/meson_deps/meson/inc')
#############################################################################
subdir('submodules/meson_deps/meson/deps/ansicodes')
subdir('submodules/meson_deps/meson/deps/parson')
subdir('submodules/meson_deps/meson/deps/djbhash')
subdir('submodules/meson_deps/meson/deps/c_stringfn')
subdir('submodules/meson_deps/meson/deps/c_string_buffer')
subdir('submodules/meson_deps/meson/deps/asprintf')
subdir('submodules/meson_deps/meson/deps/uuid4')
subdir('submodules/meson_deps/meson/deps/c_fsio')
subdir('submodules/meson_deps/meson/deps/bytes')
subdir('submodules/meson_deps/meson/deps/ms')
subdir('submodules/meson_deps/meson/deps/timestamp')
subdir('submodules/meson_deps/meson/deps/slug')
subdir('submodules/meson_deps/meson/deps/cargs')
#//////////////////////////////////////////////////////////////////////
subdir('embed-utils')
subdir('embed-test')
subdir('embed')
#//////////////////////////////////////////////////////////////////////
