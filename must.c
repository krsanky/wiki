#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "params.h"

void 		header   ();

void
web()
{
	PARAMS         *ps;
	char           *qs = getenv("QUERY_STRING");
	char           *p1;

	ps = params_create(10, qs);

	header();

	p1 = params_get(ps, "p1");
	printf("<p>%s</p>\n", p1);


	p1 = params_get(ps, "qwdqwdwqp1");
	printf("<p>[%s]</p>\n", p1);
	params_free(ps);
}

void
header()
{
	printf("Content-type: text/html\n\n");
	printf("<h1>hey!</h1>\n");
}

int
main()
{
	web();
	return EXIT_SUCCESS;
}
