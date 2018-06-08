#include "tracer.h"
#include <stdio.h>
#include <stdlib.h>

void tracer_init() {
    init_gotcha_mpi_init_final();
    init_gotcha_mpi_io();
    //    init_gotcha_silo();
}

__attribute__((constructor)) void construct_me(){
    tracer_init();
}

void tracer_finalize() {
}

__attribute__((destructor)) void destruct_me(){
    tracer_finalize();
}
