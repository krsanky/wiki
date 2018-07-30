#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
/*
	char          **ap, *argv[10], *inputstring;

	for (ap = argv; ap < &argv[9] &&
	     (*ap = strsep(&inputstring, " \t")) != NULL;) {
		if (**ap != '\0')
			ap++;
	}
	*ap = NULL;
*/
	char	*string1;
	char	*orig;

	printf("arg0:%s argc:%d\n", argv[0], argc);
	if (argc > 1) {
		printf("arg1:%s\n", argv[1]);
		string1 = argv[1];
		orig = strsep(&string1, "/");
		printf("orig:%s string1:%s\n", orig, string1);
	}

	return 0;
}
