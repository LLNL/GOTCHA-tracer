# - Try to find libsilo
# Once done this will define
#  SILO_FOUND - System has libsilo
#  SILO_INCLUDE_DIRS - The libsilo include directories
#  SILO_LIBRARIES - The libraries needed to use libsilo

FIND_PATH(WITH_SILO_PREFIX
    NAMES include/silo.h
    HINTS /usr/gapps/silo/current/$ENV{SYS_TYPE}/
)

FIND_LIBRARY(SILO_LIBRARIES
    NAMES siloh5
    HINTS ${WITH_SILO_PREFIX}/lib
)

FIND_PATH(SILO_INCLUDE_DIRS
    NAMES silo.h
    HINTS ${WITH_SILO_PREFIX}/include
)

## SILO Depends on JSON-C
FIND_LIBRARY(JSON_C_LIBRARIES
    NAMES json
    HINTS ${WITH_SILO_PREFIX}/json/lib
)
LIST(APPEND SILO_LIBRARIES ${JSON_C_LIBRARIES})

FIND_PATH(JSON_C_INCLUDE_DIRS
    NAMES json/json.h
    HINTS ${WITH_SILO_PREFIX}/json/include
)
LIST(APPEND SILO_INCLUDE_DIRS ${JSON_C_INCLUDE_DIRS})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(SILO DEFAULT_MSG
    SILO_LIBRARIES
    SILO_INCLUDE_DIRS
)

# Hide these vars from ccmake GUI
MARK_AS_ADVANCED(
	SILO_LIBRARIES
	SILO_INCLUDE_DIRS
	JSON_C_LIBRARIES
	JSON_C_INCLUDE_DIRS
)
