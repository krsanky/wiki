#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "params.h"
#include "mtemplate.h"

#include "tmpl.h"

void
showtemplate(char *t_)
{
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

	if (tmpl_readfile(t__, &template) != 0)
		printf("read_template_file() error\n");
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
	char           *tout;
	if (mtemplate_run_mbuf(t, namespace, &tout, errbuf, sizeof(errbuf)) == -1)
		errx(1, "mtemplate_run_mbuf: %s", errbuf);
	printf("<div style='color:yellow;background-color:red;'>%s</div>\n<h1>poop</h1>\n", tout);

	free(template);
	free(tout);
	mobject_free(namespace);
	mtemplate_free(t);
	free(t__);
}

/*
 * tbuf should be freed by caller.
 */
int
tmpl_readfile(char *filename, char **tbuf)
{
	int 		tfd;
	size_t 		tlen = 0;
	int 		len = 0;
	char 		buf      [8192];
	/* char           *template = NULL; */

	if ((tfd = open(filename, O_RDONLY)) == -1) {
		/* printf("err opening template file:%s", t__); */
		return -1;
	}
	/* read file into char * template */
	for (;;) {
		if ((len = read(tfd, buf, sizeof(buf))) == -1) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			/* err(1, "read"); */
			return -1;
		}
		if (len == 0) {
			break;
		}
		if (tlen + len + 1 < tlen) {
			/* errx(1, "template length exceeds SIZE_T_MAX"); */
			return -1;
		}
		if ((*tbuf = realloc(*tbuf, tlen + len + 1)) == NULL) {
			/*
			errx(1, "realloc(*tbuf, %zu) failed",
			     tlen + len + 1);
			*/
			return -1;
		}
		memcpy(*tbuf + tlen, buf, len);
		*(*tbuf + tlen + len) = '\0';
		tlen += len;
	}
	close(tfd);
	/* printf("\nraw templ.\n:<pre>\n%s\n</pre>\n", *tbuf); */

	return 0;
}

/* tmp delete */
int
tmpl_render(struct mtemplate * tmpl, struct mobject * namespace, char **buf)
{
	return mtemplate_run_mbuf(tmpl, namespace, buf, NULL, 0);
}
