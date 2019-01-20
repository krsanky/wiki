#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int fn1()
{
	return 42;
}

int
main()
{
	FILE		*fp;

	fp = fopen("NOT-A-FILE.txt", "r");
	if (fp == NULL) {
		printf("fp == NULL err:%s\n", strerror(errno));
	}

	return EXIT_SUCCESS;
}
