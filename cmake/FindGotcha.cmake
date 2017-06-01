# - Try to find libgotcha
# Once done this will define
#  GOTCHA_FOUND - System has libgotcha
#  GOTCHA_INCLUDE_DIRS - The libgotcha include directories
#  GOTCHA_LIBRARIES - The libraries needed to use libgotcha

FIND_PATH(WITH_GOTCHA_PREFIX
    NAMES include/gotcha/gotcha.h
)

FIND_LIBRARY(GOTCHA_LIBRARIES
    NAMES gotcha
    HINTS ${WITH_GOTCHA_PREFIX}/lib
)

FIND_PATH(GOTCHA_INCLUDE_DIRS
    NAMES gotcha/gotcha.h
    HINTS ${WITH_GOTCHA_PREFIX}/include
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GOTCHA DEFAULT_MSG
    GOTCHA_LIBRARIES
    GOTCHA_INCLUDE_DIRS
)

# Hide these vars from ccmake GUI
MARK_AS_ADVANCED(
	GOTCHA_LIBRARIES
	GOTCHA_INCLUDE_DIRS
)
