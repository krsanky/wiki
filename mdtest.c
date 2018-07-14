#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	//printf("%s: num-args:%d\n", argv[0], argc);
	if (argc < 2) {
		printf("%s <markdown-file>\n", argv[0]);
		exit(1);
	}
	printf("markdown-file: %s\n", argv[1]);

	int 	val;
	char 	*mdstr = "# titleasd";
	MMIOT	*mmiot;
	FILE	*mdfile, *out;

/*
	mdfile = fopen(argv[1], "r");
	if (mdfile == NULL) {
		fprintf(stderr, "cannot open input file:%s\n", argv[1]);
		exit(1);
	}
	mmiot = mkd_in(mdfile, 0);
*/

	mmiot = mkd_string(mdstr, strlen(mdstr), 0);
	out = fopen("test1.html", "w");
	if (out == NULL) {
		fprintf(stderr, "cannot open out file\n");
		exit(1);
	}

	//fprintf(out, "asdasd\n");
	printf("pre markdown\n"); 
	val = markdown(mdfile, out, 0);
	printf("markdown val:%d\n", val); 

	if (mdfile != NULL) fclose(mdfile);
	if (out != NULL) fclose(out);
	return 0;
}

