# Header files need not be enumerated
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

#################
# LIB Tracer #
#################

# installed header files
LIST(APPEND tracer_install_headers
	tracer.h
)
INSTALL(FILES ${tracer_install_headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Source files
SET(tracer_srcs
    tracer.c
)

# static library
ADD_LIBRARY(tracer STATIC ${tracer_srcs})
TARGET_LINK_LIBRARIES(tracer ${TRACER_EXTERNAL_LIBS})
SET_TARGET_PROPERTIES(tracer PROPERTIES OUTPUT_NAME tracer CLEAN_DIRECT_OUTPUT 1)
INSTALL(TARGETS tracer DESTINATION ${CMAKE_INSTALL_LIBDIR})

# shared library
ADD_LIBRARY(tracer-shared SHARED ${tracer_srcs})
TARGET_LINK_LIBRARIES(tracer-shared ${TRACER_EXTERNAL_LIBS})
SET_TARGET_PROPERTIES(tracer-shared PROPERTIES OUTPUT_NAME tracer CLEAN_DIRECT_OUTPUT 1)
INSTALL(TARGETS tracer-shared DESTINATION ${CMAKE_INSTALL_LIBDIR})
