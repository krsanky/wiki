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
	char 		t        [] = "templates/test_forms.m";


	/* <textarea name="test_forms_text" */
	if ((ctx = mdict_new()) == NULL)
		errpage("err mdict_new()");
	msgpage("msg ? %s", "string...");




	http_headers();
	myhtml_header();
	ret = tmpl_render(t, ctx);
	printf("<script>console.log('ret:%d');</script>", ret);
	myhtml_footer();
}

int
main()
{
	display();
	return EXIT_SUCCESS;
}
