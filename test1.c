#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "myhtml.h"
#include "util.h"

int
main(int argc, char **argv)
{
	int            *a;
	printf("argc:%d %s\n", argc, argv[0]);
	a = make_anchor("new", NULL, "page123.md", NULL);
	printf("a:%s\n", a);
	return 0;
}
