#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mkdio.h>

int
main(int argc, char *argv[])
{
	printf("%s: num-args:%d\n", argv[0], argc);

	char           *mdstr = "# titleasd";
	FILE           *out;

	out = fopen("tmp123.txt", "w");
	if (out == NULL) {
		fprintf(stderr, "cant open file to write");
		exit(1);
	}
	fprintf(out, "stuff\n");
	if (out != NULL)
		fclose(out);
	return 0;
}
