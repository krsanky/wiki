#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <mtemplate.h>

#include "util.h"
#include "myhtml.h"
#include "tmpl.h"

int
main()
{
	char 		t        [] = "templates/admin.m";
	http_headers();
	myhtml_header();
	tmpl_render(t, NULL);
	myhtml_footer();
	return EXIT_SUCCESS;
}
