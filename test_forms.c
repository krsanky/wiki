#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "forms.h"
#include "util.h"

char           *CT = "CONTENT_TYPE=multipart/form-data; boundary=---------------------------804515248930748430817995068";

int
main(int argc, char **argv)
{
	char           *boundary;

	printf("%s argc:%d\n", argv[0], argc);

	boundary = parse_boundary(CT);
	printf("boundary[%s]\n", boundary);

	free(boundary);
	return EXIT_SUCCESS;
}
