#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <mtemplate.h>
#include <dirent.h>

#include "util.h"
#include "tmpl.h"

int
main()
{
	int 		ret;
	char 		fn       [] = "templates/sample.m";
	struct mobject *namespace = NULL;

	if ((namespace = mdict_new()) == NULL) {
		printf("mdict_new error");
		goto end;
	}
	mdict_insert_ss(namespace, "var1", "var1 example ...");

	http_headers();
	ret = tmpl_render(fn, namespace);

end:
	mobject_free(namespace);
	return 0;
}