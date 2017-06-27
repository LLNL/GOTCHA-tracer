#ifndef __TRACER_H
#define __TRACER_H

#ifdef __cplusplus
extern "C" {
#endif

// Modules

void init_gotcha_mpi_io();
void init_gotcha_mpi_init_final();
void init_gotcha_silo();

// Core functionality

void tracer_init();
void tracer_finalize();

#ifdef __cplusplus
};
#endif

#endif
