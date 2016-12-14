# Find the header files

unset(TOOLS_INCLUDE_DIR CACHE)
FIND_PATH(TOOLS_INCLUDE_DIR tools/sampler/sampler.h
  /usr/local/include
  /usr/include
  #/opt/local/include
  #/sw/local/include
  #/sw/include
  #NO_DEFAULT_PATH
  )

#if (TOOLS_INCLUDE_DIR)
#  message(STATUS "Includes (tools) found in ${TOOLS_INCLUDE_DIR}")
#else()
#  message(FATAL_ERROR "Includes (tools) not found")
#endif()

# Macro to unify finding both the debug and release versions of the
# libraries; this is adapted from the OpenSceneGraph FIND_LIBRARY
# macro.

MACRO(FIND_TOOLS_LIBRARY MYLIBRARY MYLIBRARYNAME)
  FIND_LIBRARY(${MYLIBRARY}
    NAMES "tools_${MYLIBRARYNAME}"
    PATHS
    ${TOOLS_ROOT}/build/lib
    $ENV{TOOLS_ROOT}/build/lib
    NO_DEFAULT_PATH
    )
ENDMACRO(FIND_TOOLS_LIBRARY LIBRARY LIBRARYNAME)

FIND_TOOLS_LIBRARY(TOOLS_IOFUNCTIONS_LIBRARY io_functions)
FIND_TOOLS_LIBRARY(TOOLS_IMAGEPROCESSING_LIBRARY image_processing)
FIND_TOOLS_LIBRARY(TOOLS_PROGRAMOPTIONS_LIBRARY program_options)
FIND_TOOLS_LIBRARY(TOOLS_SAMPLER_LIBRARY sampler)