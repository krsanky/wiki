#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "params.h"
#include "tmpl.h"

void
web()
{
	PARAMS         *ps;
	char           *qs = getenv("QUERY_STRING");
	char           *t = NULL;

	if (qs != NULL) {
		ps = params_create(10, qs);
		t = params_get(ps, "t");
		if (t != NULL)
			t = strdup(t);
		params_free(ps);
	}
	if (t != NULL) {
		printf("<h1>t:[%s]</h1>\n", t);
		showtemplate(t);
	} else {
		printf("<h1>t NULL</h1>\n");
	}
	free(NULL);
	free(t);
}

void
header()
{
	printf("Content-type: text/html\n\n");
	printf("<h1>hey</h1>\n");
}

int
main2()
{
	header();
	web();

	return EXIT_SUCCESS;
}
