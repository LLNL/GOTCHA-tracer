PROJECT(tracer_Tests)

# MPI HELLO WORLD

## augmented to call tracer
ADD_EXECUTABLE(mpi_hello_aug mpi_hello_aug.c)
TARGET_LINK_LIBRARIES(mpi_hello_aug tracer)
ADD_TEST(NAME hello_linked COMMAND ./mpi_hello_aug)

## original: trace with LD_PRELOAD
ADD_EXECUTABLE(mpi_hello mpi_hello.c)
TARGET_LINK_LIBRARIES(mpi_hello ${MPI_C_LIBRARIES})
ADD_TEST(NAME hello_ldload COMMAND ./mpi_hello)
SET_TESTS_PROPERTIES(hello_ldload PROPERTIES ENVIRONMENT "LD_PRELOAD=../src/libtracer.so")

# SILO FILE TEST

IF(GT_BUILD_SILO)
## augmented to call tracer
ADD_EXECUTABLE(silo_test_aug silo_test_aug.c)
TARGET_LINK_LIBRARIES(silo_test_aug tracer)
ADD_TEST(NAME silo_linked COMMAND ./silo_test_aug)

## original: trace with LD_PRELOAD
ADD_EXECUTABLE(silo_test silo_test.c)
TARGET_LINK_LIBRARIES(silo_test ${SILO_LIBRARIES} m)
ADD_TEST(NAME silo_ldload COMMAND ./silo_test)
SET_TESTS_PROPERTIES(silo_ldload PROPERTIES ENVIRONMENT "LD_PRELOAD=../src/libtracer.so")
ENDIF(GT_BUILD_SILO)

# "make check"
# prints output from the ctests to verify traces
ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
