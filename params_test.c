#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"

int
main(int argc, char **argv)
{
	printf("%s argc:%d\n", argv[0], argc);
	params_test();	
	return EXIT_SUCCESS;
}
