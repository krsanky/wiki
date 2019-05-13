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
	int 		ret;
	struct mobject *ctx = NULL;
	char 		t        [] = "templates/test_codemirror.m";

	if ((ctx = mdict_new()) == NULL)
		errpage("err mdict_new()");


	http_headers();
	myhtml_header(ctx);
	ret = tmpl_render(t, ctx);
	printf("<script>console.log('ret:%d');</script>\n", ret);

	printf("<script src='/static/codemirror-5.46.0/lib/codemirror.js'></script>\n");
	printf("<link rel='stylesheet' href='/static/codemirror-5.46.0/lib/codemirror.css'>\n");

	myhtml_footer();
}

int
main()
{
	display();
	return EXIT_SUCCESS;
}
