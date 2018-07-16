#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "wiki.h"
#include "myhtml.h"
#include "yuarel.h"

extern char **environ;

void 
query_params_test(struct yuarel_param *params, int sz)
{
	char *qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errorpage("error with QUERY_STRING");
		return;
	}

	if (sz < 0) {
		errorpage("error with yuarel_parse_query()");
		return;
	}

	printf("HTTP/1.0 200 OK\n");
	printf("Content-type: text/html\n\n");

	myhtml_header();
	myhtml_topnav();
	printf("<hr/>\n");
	printf("<dl>\n");
	while (sz-- > 0) {
		printf("<dt>%s</dt><dd>%s</dd>\n", params[sz].key, params[sz].val);
	}
	printf("</dl>\n");

	myhtml_footer();
}

void 
mainpage(void)
{
	printf("HTTP/1.0 200 OK\n");
	printf("Content-type: text/html\n\n");

	myhtml_header();
	myhtml_topnav();
	printf("<hr/>\n");
	printf("\
<p>wiki wiki wiki</p>\n");

	showenv();

	myhtml_footer();
}

void
errorpage(char *error) 
{
	printf("HTTP/1.0 200 OK\n");
	printf("Content-type: text/html\n\n");

	myhtml_header();
	myhtml_topnav();
	printf("<hr/>\n");
	printf("\
<p style='color:red;'>%s</p>\n", error);
	myhtml_footer();
}

void
showenv()
{
	printf("<pre>\n");
	char *data = getenv("QUERY_STRING");
	if(data == NULL)
  		printf("Error! Error in passing data from form to script.\n");
	else
		printf("QUERY_STRING[%s]\n", data);

	puts("---------------");

	for (char **env = environ; *env; ++env)
        printf("%s\n", *env);
	
	printf("</pre>\n");

}
