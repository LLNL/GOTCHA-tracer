FUNCTION(GENERATE_MODULE module_name)
        ADD_CUSTOM_COMMAND(OUTPUT gotcha_${module_name}.c
                COMMAND python translate.py ${module_name}
                COMMAND ${CMAKE_COMMAND} -E copy gotcha_${module_name}.c ${CMAKE_CURRENT_BINARY_DIR}/gotcha_${module_name}.c
                DEPENDS ${module_name}.txt
                DEPENDS translate.py
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
        SET_SOURCE_FILES_PROPERTIES(gotcha_${module_name}.c PROPERTIES GENERATED TRUE)
        ADD_LIBRARY(gotcha_${module_name} STATIC gotcha_${module_name}.c)
        TARGET_LINK_LIBRARIES(gotcha_${module_name} ${DIO_EXTERNAL_LIBS})

        LIST(APPEND MODULE_LIBS gotcha_${module_name})
        SET(MODULE_LIBS ${MODULE_LIBS} PARENT_SCOPE)
ENDFUNCTION(GENERATE_MODULE)

LIST(APPEND modules
        mpi_init_final
        mpi_io
        silo
)

FOREACH(m IN ITEMS ${modules})
        GENERATE_MODULE(${m})
ENDFOREACH()

SET(MODULE_LIBS ${MODULE_LIBS} PARENT_SCOPE)
