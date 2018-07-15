#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "wiki.h"
#include "myhtml.h"
#include "yuarel.h"

extern char **environ; /* not used, maybe delete eventually ... */

/* 
 * All major routines should have a comment briefly describing what 
 * they do.  The comment before the "main" routine should describe 
 * what the program does. 
 */ 
int 
main(void)
{
	char *qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errorpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}

	int p;
	struct yuarel_param params[10];
	p = yuarel_parse_query(qs, '&', params, 10);

	printf("HTTP/1.0 200 OK\n");
	printf("Content-type: text/html\n\n");

	myhtml_header();
	myhtml_topnav();
	printf("<hr/>\n");
	printf("<dl>\n");
	while (p-- > 0) {
		printf("<dt>%s</dt><dd>%s</dd>\n", params[p].key, params[p].val);
	}
	printf("</dl>\n");

	myhtml_footer();
	return EXIT_SUCCESS;
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
