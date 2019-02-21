#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <mtemplate.h>

#include "wiki.h"
#include "forms.h"
#include "util.h"
#include "myhtml.h"
#include "tmpl.h"

void
display()
{
	struct mobject *ctx = NULL;
	char 		t        [] = "templates/fix_perms.m";

	if ((ctx = mdict_new()) == NULL)
		errpage("err mdict_new()");

	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(NULL, NULL, NULL);
	tmpl_render(t, ctx);
	printf("<script>console.log('fix permissions...');</script>\n");
	myhtml_footer();
}

int
main()
{
	display();
	return EXIT_SUCCESS;
}
