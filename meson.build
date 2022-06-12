project('c_embed', ['c'],
  default_options: [
   'warning_level=0',
   'c_std=gnu99',
  ]
)
#############################################################
cc = meson.get_compiler('c')
#//***********************************************************/
#############################################################
fs = import('fs')
pkg_config = import('pkgconfig')
#############################################################
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
add_project_arguments('-Wno-unused-value', language : 'c')
add_project_arguments('-Wno-gnu-alignof-expression', language : 'c')
add_project_arguments('-Wno-varargs', language : 'c')
add_project_arguments('-Wno-return-type', language : 'c')
pwd_bin = find_program('pwd', required : true)
pwd = run_command(pwd_bin, check: true).stdout().strip()
meson_deps_dir = pwd+'/submodules/meson_deps'
#############################################################################
inc = include_directories(
  'submodules/meson_deps',
  'submodules/meson_deps/submodules',
  'submodules/meson_deps/submodules/c_fsio/include',
  'submodules/meson_deps/submodules/slug.c/src',
  'submodules/meson_deps/submodules/slug.c/deps',
  'submodules/meson_deps/submodules/slug.c',
  'submodules/meson_deps/submodules/djbhash/src',
  'submodules/meson_deps/submodules/djbhash',
  'submodules/meson_deps/submodules/c_string_buffer/include',
  'submodules/meson_deps/submodules/c_stringfn/include',
  'submodules/meson_deps/submodules/greatest',
  'submodules/meson_deps/submodules/uuid4',
  'embed',
  './',
  '../',
  '../../../',
)
#//***********************************************************/
#//////////////////////////////////////////////////////////////////////
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
