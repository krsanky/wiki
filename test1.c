#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	printf("arg0:%s argc:%d\n", argv[0], argc);
	if (argc > 1) {
		printf("arg1:%s\n", argv[1]);
	}
	return 0;
}
