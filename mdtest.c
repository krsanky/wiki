#include <stdio.h>
#include <mkdio.h>

/*
LIBRARY
     Markdown (libmarkdown, -lmarkdown)

SYNOPSIS
     #include <mkdio.h>

     MMIOT
     *mkd_in(FILE *input, int flags);

     MMIOT
     *mkd_string(char *string, int size, int flags);

     int
     markdown(MMIOT *doc, FILE *output, int flags);
*/

int 
main(int argc, char * argv[]) 
{
	printf("%s: num-args:%d\n", argv[0], argc);
				
	for (int i=0; i<argc; i++) {
		printf("arg-%d %s\n", i, argv[i]);
	}

	return 0;
}

