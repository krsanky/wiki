#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int fn1()
{
	return 42;
}

int
main()
{
	printf("errno...\n");
	printf("fn1:%d\n", fn1());
	return EXIT_SUCCESS;
}
