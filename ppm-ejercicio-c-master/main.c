#ifndef LIBS
#define LIBS
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "ppm-operations.h"
#include "aux_operations.h"
#include <getopt.h>
#include <math.h>
#endif

extern int errno;
extern FILE *f, * op;
extern t_ppm p_op;
extern char output_filename[1024];

int main(int argc, char * argv[]) {

  if (!options_handling(argc,argv))
  {
    ppm_save(p_op, op);

    /* Output file closed and PPM struct must free its memory */
    fclose(op);
    ppm_free(p_op);

    /* Input file closed*/
    fclose(f);
  }
  exit(EXIT_SUCCESS);
}
