#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "util.h"
#include "myhtml.h"
#include "wiki.h"
#include "mtemplate.h"
#include "tmpl.h"

int
main()
{

	http_headers();
	myhtml_header();
	printf("<p style='color:green;'>test_altstyle</p>\n");


	char 		t        [] = "test_altstyle";
	char           *tp;
	tp = tmpl_path(t);
	printf("<p>tp:%s</p>\n", tp);
	free(tp);

	myhtml_set_altstyle("s1");
	tp = tmpl_path(t);
	printf("<p>tp:%s</p>\n", tp);
	free(tp);

	myhtml_footer();

	return EXIT_SUCCESS;
}
