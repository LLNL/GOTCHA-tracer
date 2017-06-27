#include <silo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NDIMS 3
#define NZONES 4
#define NNODES 13

int
main(int argc, char *argv[])
{
    int             nnodes = NNODES;
    int             nzones = NZONES;
    int             nodelist[23];
    int             shapesize[] = {8, 4, 5, 6};
    int             shapecnt[] = {1, 1, 1, 1};
    char            mesh_command[256];
    int             len;
    char           *filename = "alltypes.silo";
    int		    driver = DB_PDB;

    DBfile         *dbfile = NULL;
    int             ndims = NDIMS;
    int             dims[NDIMS];
    double         *coords[NDIMS];
    double          x[NNODES];
    double          y[NNODES];
    double          z[NNODES];

    DBfacelist     *facelist = NULL;

    double          nodal[NNODES];
    double          zonal[NZONES];
    int             matlist[NZONES];
    int             mats[] = {1,2,3,4};

    int             i,j;

    const int       origin = 0;
    int             show_all_errors = FALSE;

    /* Parse command-line options */
/*    for (i=1; i<argc; i++) {
	if (!strncmp(argv[i], "DB_PDB",6)) {
	    driver = StringToDriver(argv[i]);
	    filename = "alltypes.pdb";
	} else if (!strncmp(argv[i], "DB_HDF5", 7)) {
	    driver = StringToDriver(argv[i]);
	    filename = "alltypes.h5";
        } else if (!strcmp(argv[i], "show-all-errors")) {
            show_all_errors = 1;
	} else if (argv[i][0] != '\0') {
	    fprintf(stderr, "unknown option: %s\n", argv[i]);
	    exit(1);
	}
    }
*/
    tracer_init();
    
    /* Turn on error handling */
    DBShowErrors(show_all_errors?DB_ALL_AND_DRVR:DB_ABORT, NULL);
    DBSetFriendlyHDF5Names(2);

    /* Create file */
    printf("Creating test file \"%s\".\n", filename);
    dbfile = DBCreate(filename, DB_CLOBBER, DB_LOCAL, "3D ucd", driver);

    i = 0;

    /* 0 */
    x[i] = 0.5;
    y[i] = 1.0;
    z[i++] = 0.0;

    /* 1 */
    x[i] = 1.5;
    y[i] = 1.0;
    z[i++] = 0.0;

    /* 2 */
    x[i] = 1.5;
    y[i] = 1.0;
    z[i++] = 1.0;

    /* 3 */
    x[i] = 0.5;
    y[i] = 1.0;
    z[i++] = 1.0;

    /* 4 */
    x[i] = 0.5;
    y[i] = 2.0;
    z[i++] = 0.0;

    /* 5 */
    x[i] = 1.5;
    y[i] = 2.0;
    z[i++] = 0.0;

    /* 6 */
    x[i] = 2.5;
    y[i] = 2.0;
    z[i++] = 0.0;

    /* 7 */
    x[i] = 2.5;
    y[i] = 2.0;
    z[i++] = 1.0;

    /* 8 */
    x[i] = 1.5;
    y[i] = 2.0;
    z[i++] = 1.0;

    /* 9 */
    x[i] = 0.5;
    y[i] = 2.0;
    z[i++] = 1.0;

    /* 10 */
    x[i] = 0.0;
    y[i] = 3.0;
    z[i++] = 0.5;

    /* 11 */
    x[i] = 1.0;
    y[i] = 3.0;
    z[i++] = 0.5;

    /* 12 */
    x[i] = 2.0;
    y[i] = 3.0;
    z[i++] = 0.5;

    coords[0] = x;
    coords[1] = y;
    coords[2] = z;

    DBPutUcdmesh(dbfile, "mesh", 3, NULL, (void *)coords, nnodes, nzones, "zonelist",
                 "facelist", DB_DOUBLE, NULL);

    i = 0;
    /* Hex */
    nodelist[i++] = 4;
    nodelist[i++] = 5;
    nodelist[i++] = 8;
    nodelist[i++] = 9;
    nodelist[i++] = 0;
    nodelist[i++] = 1;
    nodelist[i++] = 2;
    nodelist[i++] = 3;

    /* Tet */
    nodelist[i++] = 10;
    nodelist[i++] = 4;
    nodelist[i++] = 11;
    nodelist[i++] = 9;

    /* Pyramid */
    nodelist[i++] = 4;
    nodelist[i++] = 5;
    nodelist[i++] = 8;
    nodelist[i++] = 9;
    nodelist[i++] = 11;

    /* Prism */
    nodelist[i++] = 5;
    nodelist[i++] = 6;
    nodelist[i++] = 7;
    nodelist[i++] = 8;
    nodelist[i++] = 11;
    nodelist[i++] = 12;

    for (j=0; j<i; j++)
        nodelist[j] += origin;

    DBSetDeprecateWarnings(0);
    DBPutZonelist(dbfile, "zonelist", nzones, ndims, nodelist, 23, origin,
                  shapesize, shapecnt, 4);
    DBSetDeprecateWarnings(3);

    facelist = DBCalcExternalFacelist(nodelist, nnodes, origin,
                                      shapesize, shapecnt, 4, NULL, 0);

    DBPutFacelist(dbfile, "facelist", facelist->nfaces, facelist->ndims,
               facelist->nodelist, facelist->lnodelist, facelist->origin,
               facelist->zoneno, facelist->shapesize, facelist->shapecnt,
                  facelist->nshapes, facelist->types, facelist->typelist,
                  facelist->ntypes);

    for(i=0;i<nnodes;i++)
        nodal[i] = x[i];

    zonal[0] = 4.0;
    zonal[1] = 2.0;
    zonal[2] = 0.0;
    zonal[3] = 7.0;

    DBPutUcdvar1(dbfile, "nodal", "mesh", (void*)nodal, nnodes, NULL, 0,
                 DB_DOUBLE, DB_NODECENT, NULL);

    DBPutUcdvar1(dbfile, "zonal", "mesh", (void*)zonal, nzones, NULL, 0,
                 DB_DOUBLE, DB_ZONECENT, NULL);

    matlist[0] = 1;
    matlist[1] = 2;
    matlist[2] = 3;
    matlist[3] = 4;

    dims[0] = nzones;
    DBPutMaterial(dbfile, "mat", "mesh", 4, mats, matlist, dims, 1, NULL, NULL,
                  NULL, NULL, 0, DB_DOUBLE, NULL);

    sprintf(mesh_command, "mesh mesh");
    len = strlen(mesh_command) + 1;
    DBWrite(dbfile, "_meshtvinfo", mesh_command, &len, 1, DB_CHAR);

    DBClose(dbfile);

    DBFreeFacelist(facelist);

//    CleanupDriverStuff();
    return 0;
}
