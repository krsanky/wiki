#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define c1 "CONSTANT-123"

int
main(int argc, char **argv)
{
	char           *buf;
	int 		bufl;
	/*
		printf("%s\n", argv[0]);
		printf("sizeof[%s][%lu]\n", c1, sizeof(c1));
	*/
	/* sizeof[CONSTANT-123][13] */

	if (argc > 1) {
		printf("arg1:%s\n", argv[1]);
		bufl = strlen(argv[1]) + 4;
		buf = malloc(bufl);
		printf("strlen arg1:%lu sizeof-buf:%lu\n", strlen(argv[1]), sizeof(buf));
		strlcpy(buf, "LOG", bufl);
		strlcat(buf, argv[1], bufl);
		printf("buf:%s\n", buf);
	}
	return 0;
}
