#include <stdio.h>
#include <stdlib.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

FILE *logfile;

/* 
 * All major routines should have a comment briefly describing what 
 * they do.  The comment before the "main" routine should describe 
 * what the program does. 
 */ 
int 
main(int argc, char ** argv)
{
	printf("I am %s\n", argv[0]);

	logfile = fopen("log.txt", "a");
	fprintf(logfile, "main...\n");

	if (logfile != NULL) fclose(logfile);
	return 0;
}

