# include libfind
include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(RAT_MLFMM_PKGCONF RAT_MLFMM)

# Include dir
find_path(RAT_MLFMM_INCLUDE_DIR
  NAMES mlfmm/mlfmm.hh
  PATHS ${RAT_MLFMM_PKGCONF_INCLUDE_DIR}
  HINTS /usr/local/include/rat
)

# Finally the library itself
find_library(RAT_MLFMM_LIBRARY
  NAMES rat-mlfmm-st
  PATHS ${RAT_MLFMM_PKGCONF_LIBRARY_DIR}
  HINTS /usr/local/lib/rat/mlfmm
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(RAT_MLFMM_PROCESS_INCLUDES RAT_MLFMM_INCLUDE_DIR)
set(RAT_MLFMM_PROCESS_LIBS RAT_MLFMM_LIBRARY)
libfind_process(RAT_MLFMM)

