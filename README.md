# GOTCHA Tracer

This is a simple example for how to create a tracer using [GOTCHA](https://github.com/llnl/GOTCHA).
It is also shows how a CMake project would integrate Gotcha.
This includes testing Gotcha via direct invocation and using `LD_PRELOAD`.

## Tracer Generation

There are 3 steps to creating a tracer:

1. The function protypes for the functions to trace are added in a `modules/<module-name>.txt` file.
2. Through the functionality in `modules/translate.py`, the gotcha wrapers and wrapees for each module are generated.
3. All genetared modules are linked into the main trace library (see `src/`).

## Sample Tracers

There are 3 example tracing modules included here:

- MPI init and finalize routines
- MPI IO routines
- SILO routines

## Contact/Legal

The license is [LGPL](LGPL).

This example was created by Elsa Gonsiorowski (gonsie@llnl.gov).
It utilizes the [LLNL/GOTCHA](https://github.com/llnl/GOTCHA) project.
GOTCHA was developed at LLNL by David Poliakoff and Matt Legendre.
