#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>

#include "myhtml.h"
#include "util.h"

int
main()
{
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(NULL, NULL, NULL);
	myhtml_footer();
	return EXIT_SUCCESS;
}
