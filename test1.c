#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
teststrsep(char *str)
{
	char           *str2;

	do {
		str2 = strsep(&str, "/");
		printf("str2:%s str:%s\n", str2, str);
	} while (str != NULL);
}

int
main(int argc, char **argv)
{
	printf("arg0:%s argc:%d\n", argv[0], argc);
	if (argc > 1) {
		teststrsep(argv[1]);
	}
	/*
	 * arg0:./a.out argc:2 arg1:asd/123/rtyrty/456 str2:asd
	 * string1:123/rtyrty/456
	 */

	return 0;
}
