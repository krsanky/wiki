#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>

#include "myhtml.h"
#include "util.h"

int		len = 10000;

int
main()
{
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(NULL, NULL, NULL);

	printf("<ul>\n");
	for (int i=0; i<len; i++) {
		printf("<li>%d:<a href='/long_page.cgi'>long_page</a></li>\n", i);
	}
	printf("</ul>\n");

	myhtml_footer();
	return EXIT_SUCCESS;
}
