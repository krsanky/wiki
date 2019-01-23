#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#include "util.h"
#include "myhtml.h"
#include "params.h"
#include "wiki.h"

const int 	NUM_HTTP_PARAMS = 10;

int
main(void)
{
	char           *qs;
	PARAMS         *ps;
	char           *page;
	char           *dir;

	qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	nlog("main.c main() QUERY_STRING:%s", qs);

	if ((ps = params_create(NUM_HTTP_PARAMS, qs)) == NULL) {
		errpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	if (strlen(qs) < 1) {
		wikiindex2(NULL);
	} else if (strcmp(ps->params[0].key, "index") == 0) {
		wikiindex2(params_get(ps, "d"));
	} else if (strcmp(ps->params[0].key, "view") == 0) {
		page = params_get(ps, "p");
		if (page != NULL) {
			nlog("main view param:%s", page);
			wikiview(params_get(ps, "d"), page);
		} else
			errpage("param p (page) not found");
	} else if (strcmp(ps->params[0].key, "edit") == 0) {
		page = params_get(ps, "p");
		dir = params_get(ps, "d");
		wikiedit(dir, page);
	} else if (strcmp(ps->params[0].key, "editform") == 0) {
		wikieditform();
	} else if (strcmp(ps->params[0].key, "new") == 0) {
		wikinew(params_get(ps, "d"));
	} else if (strcmp(ps->params[0].key, "newform") == 0) {
		wikinewform();
	} else if (strcmp(ps->params[0].key, "delete") == 0) {
		page = params_get(ps, "p");
		dir = params_get(ps, "d");
		wikidelete(dir, page);
	}
	params_free(ps);
	return EXIT_SUCCESS;
}
