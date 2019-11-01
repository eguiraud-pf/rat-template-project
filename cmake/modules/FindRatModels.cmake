# include libfind
include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(RAT_MODELS_PKGCONF RAT_MODELS)

# Include dir
find_path(RAT_MODELS_INCLUDE_DIR
  NAMES models/modelcoil.hh
  PATHS ${RAT_MODELS_PKGCONF_INCLUDE_DIR}
  HINTS /usr/local/include/rat
)

# Finally the library itself
find_library(RAT_MODELS_LIBRARY
  NAMES rat-models-st
  PATHS ${RAT_MODELS_PKGCONF_LIBRARY_DIR}
  HINTS /usr/local/lib/rat/models
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(RAT_MODELS_PROCESS_INCLUDES RAT_MODELS_INCLUDE_DIR)
set(RAT_MODELS_PROCESS_LIBS RAT_MODELS_LIBRARY)
libfind_process(RAT_MODELS)

