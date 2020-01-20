#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mtemplate.h>
#include <dirent.h>
#include <assert.h>

#include "util.h"
#include "tmpl.h"
#include "myhtml.h"

int
main()
{
	char 		t       [] = "templates/sample.m";
	struct mobject *data = NULL;

	assert((data = myhtml_data_new()) != NULL);

	mdict_insert_ss(data, "var1", "var1 example ...");

	http_headers();
	myhtml_header(data);

	tmpl_render(t, data);

	myhtml_footer(data);

	mobject_free(data);
	return EXIT_SUCCESS;
}
