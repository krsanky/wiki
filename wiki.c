#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* 
 * All major routines should have a comment briefly describing what 
 * they do.  The comment before the "main" routine should describe 
 * what the program does. 
 */ 
int 
main(int argc, char * argv[]) 
{
	//printf("%s: num-args:%d\n", argv[0], argc);

	printf("HTTP/1.0 200 OK\n");
	printf("Content-type: text/html\n\n");
	printf("<p>test</p>\n");

	return 0;
}

