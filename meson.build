project(
  'fpt-dds',
  ['fortran'],
  version: run_command(meson.current_source_dir()/'version.sh', check: true).stdout().strip(),
  meson_version: '>=1.2'
)

meson.add_dist_script('version.sh')

# Subdirectories
subdir('src')

# Install headers
install_subdir(
  'include',
  strip_directory: true,
  install_dir: get_option('includedir')
)
 
