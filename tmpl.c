#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "params.h"

void
web()
{
	PARAMS         *ps;
	char           *qs = getenv("QUERY_STRING");
	char           *p1;



	if (qs != NULL) {
		ps = params_create(10, qs);
		p1 = params_get(ps, "p1");
		printf("<p>%s</p>\n", p1);


		p1 = params_get(ps, "qwdqwdwqp1");
		if (p1 != NULL) 
			printf("<p>p1:[%s]</p>\n", p1);
		else
			printf("<p>no p1</p>\n");
		params_free(ps);
	}
	printf("<pre>asd\n");
	printf("</pre>\n");
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
	header();
	web();

	return EXIT_SUCCESS;
}




