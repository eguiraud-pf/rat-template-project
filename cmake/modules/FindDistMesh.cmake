# include libfind
include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(DISTMESH_PKGCONF DISTMESH)

# Include dir
find_path(DISTMESH_INCLUDE_DIR
  NAMES distmesh/distmesh2d.hh
  PATHS ${DISTMESH_PKGCONF_INCLUDE_DIR}
  HINTS /usr/local/include/rat
)

# Finally the library itself
find_library(DISTMESH_LIBRARY
  NAMES distmesh
  PATHS ${DISTMESH_PKGCONF_LIBRARY_DIR}
  HINTS /usr/local/lib/rat/distmesh
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(DISTMESH_PROCESS_INCLUDES DISTMESH_INCLUDE_DIR)
set(DISTMESH_PROCESS_LIBS DISTMESH_LIBRARY)
libfind_process(DISTMESH)

