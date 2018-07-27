#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define c1 "CONSTANT-123"

int
main(int argc, char **args)
{
	printf("%s\n", args[0]);
	printf("sizeof[%s][%lu]\n", c1, sizeof(c1));
	/* sizeof[CONSTANT-123][13] */

	return 0;
}
 
