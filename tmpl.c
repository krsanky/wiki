#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "mtemplate.h"
#include "params.h"

void
showtemplate(char *t_)
{
	int 		tfd;
	char           *t__;
	int 		t__l;
	char           *template = NULL;
	struct mobject *namespace = NULL;
	struct mobject *tmp;
	struct mtemplate *t;

	t__l = strlen("templates") + 1 + strlen(t_) + 1;
	t__ = malloc(t__l);
	if (t__ == NULL) {
		printf("malloc err");
		return;
	}
	strlcpy(t__, "templates", t__l);
	strlcat(t__, "/", t__l);
	strlcat(t__, t_, t__l);

	if ((tfd = open(t__, O_RDONLY)) == -1) {
		printf("err opening template file:%s", t__);
	} else {
		printf("success opening templ. file");
	}

	size_t 		tlen = 0;
	int 		len = 0;
	char 		buf      [8192];
	/* read file into char * template */
	for (;;) {
		if ((len = read(tfd, buf, sizeof(buf))) == -1) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			err(1, "read");
		}
		if (len == 0)
			break;
		if (tlen + len + 1 < tlen)
			errx(1, "template length exceeds SIZE_T_MAX");
		if ((template = realloc(template, tlen + len + 1)) == NULL)
			errx(1, "realloc(template, %zu) failed",
			     tlen + len + 1);
		memcpy(template + tlen, buf, len);
		*(template + tlen + len) = '\0';
		tlen += len;
	}
	close(tfd);
	printf("\nraw templ.\n:<pre>\n%s\n</pre>\n", template);

	/* instantiate mtemplate object */
	char 		errbuf   [1024];
	if ((t = mtemplate_parse(template, errbuf, sizeof(errbuf))) == NULL)
		printf("mtemplate_parse error\n");

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



	/*
	 * Run the template with this namespace, and send the output to
	 * stdout
	if (mtemplate_run_stdio(t, namespace, stdout, errbuf, sizeof(errbuf)) == -1)
		errx(1, "mtemplate_run_stdio: %s", errbuf);
	 */
	char *tout;
	if (mtemplate_run_mbuf(t, namespace, &tout, errbuf, sizeof(errbuf)) == -1)
		errx(1, "mtemplate_run_mbuf: %s", errbuf);
	printf("<div style='color:yellow;background-color:red;'>%s</div>\n<h1>poop</h1>\n", tout);

	free(tout);
	mobject_free(namespace);
	mtemplate_free(t);
	free(t__);
}

void
web()
{
	PARAMS         *ps;
	char           *qs = getenv("QUERY_STRING");
	char           *t = NULL;

	if (qs != NULL) {
		ps = params_create(10, qs);
		t = params_get(ps, "t");
		if (t != NULL)
			t = strdup(t);
		params_free(ps);
	}
	if (t != NULL) {
		printf("<h1>t:[%s]</h1>\n", t);
		showtemplate(t);
	} else {
		printf("<h1>t NULL</h1>\n");
	}
	free(NULL);
	free(t);
}

void
header()
{
	printf("Content-type: text/html\n\n");
}

int
main()
{
	header();
	web();

	return EXIT_SUCCESS;
}
