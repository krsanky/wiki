#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "mtemplate.h"

#include "tmpl.h"

/*
 * caller needs to mobject_free(namespace);
 */
struct mobject *
make_dummy_namespace()
{
	struct mobject *namespace = NULL;
	struct mobject *tmp;

	/* initialize template namespace object */
	if ((namespace = mdict_new()) == NULL)
		printf("mdict_new error");

	/* Add some values to the namespace (ignoring errors) */
	mdict_insert_ss(namespace, "program_name", "example");	/* String */
	mdict_insert_si(namespace, "program_version", 2008);	/* Integer */
	mdict_insert_sa(namespace, "features");	/* Empty array */
	mdict_insert_sd(namespace, "credits");	/* Empty dictionary */

	/* Fill in the array and dictionary */
	tmp = mdict_item_s(namespace, "features");
	marray_append_s(tmp, "hydrocoptic marzelvanes");
	marray_append_s(tmp, "baseplate of prefamulated ammulite");
	tmp = mdict_item_s(namespace, "credits");
	mdict_insert_ss(tmp, "author", "Unknown");
	mdict_insert_si(tmp, "Copyright", 2007);

	return namespace;
}

void
_render(char *tmplfn, struct mobject * namespace)
{
	int 		ret = -1;
	char           *tbuf = NULL;
	struct mtemplate *t = NULL;
	char           *tout = NULL;

	printf("tmpl_readfile fn:%s\n", tmplfn);
	ret = tmpl_readfile(tmplfn, &tbuf);
	if (ret != 0) {
		printf("error ret:%d\n", ret);
		goto end;
	}
	if ((t = mtemplate_parse(tbuf, NULL, 0)) == NULL) {
		printf("mtemplate_parse error\n");
		goto end;
	}

	/* store template in var , and printf it */
	if (mtemplate_run_mbuf(t, namespace, &tout, NULL, 0) == -1) {
		printf("error mtemplate_run_mbuf");
		goto end;
	}
	printf("<div style='color:yellow;background-color:red;'>%s</div>\n", tout);

	/* output templatye directly to stdio */
	if (mtemplate_run_stdio(t, namespace, stdout, NULL, 0) == -1) {
		printf("error mtemplate_run_mbuf");
		goto end;
	}
	/*
	goto l2;
	printf("pre l2\n");
	l2:
	printf("post l2\n");
	*/

end:
	free(tbuf);
	free(tout);
	if (t == NULL)
		mtemplate_free(t);
}

int
main()
{
	int 		ret;
	char 		fn       [] = "templates/t1.m";
	char           *buf;

	printf("test tmpl_readfile(): %s\n", fn);
	ret = tmpl_readfile(fn, &buf);
	if (ret == 0)
		printf("buf:\n%s\n", buf);
	else
		printf("error ret:%d\n", ret);
	free(buf);

	struct mobject *namespace = NULL;
	namespace = make_dummy_namespace();

	_render(fn, namespace);

	mobject_free(namespace);
	return 0;
}
