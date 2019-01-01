#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "myhtml.h"
#include "params.h"
#include "wiki.h"

#include "settings.h"
#include "util.h"

int
main(void)
{
	char           *qs;
	PARAM          *params;
	PARAMS         *ps;
	char           *param;
	char           *page;
	char           *dir;
	char           *val;
	char           *msg;
	int 		ret;

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
		wikiindex(NULL);
	} else if (strcmp(ps->params[0].key, "start") == 0) {
		msgpage("start");
	} else if (strcmp(ps->params[0].key, "logtest") == 0) {
		if (ps->params[0].val != NULL)
			val = ps->params[0].val;
		else
			val = "NO VALUE";
		msg = "logtest";
		if (ps->params[0].val != NULL) {
			msg = ps->params[0].val;
		}
		if ((ret = wikilog(val)) < 0) {
			errpage(msg);
		} else {
			msgpage(msg);
		}
	} else if (strcmp(ps->params[0].key, "index") == 0) {
		wikiindex(params_get(ps, "d"));
	} else if (strcmp(ps->params[0].key, "view") == 0) {
		param = params_get(ps, "p");
		nlog("main view param:%s", param);
		if (param != NULL)
			wikiview(params_get(ps, "d"), param);
		else
			errpage("param p (page) not found");
	} else if (strcmp(ps->params[0].key, "edit") == 0) {
		page = params_get(ps, "p");
		dir = params_get(ps, "d");
		wikiedit(dir, page);
	} else if (strcmp(ps->params[0].key, "editform") == 0) {
		wikieditform();
	} else if (strcmp(ps->params[0].key, "new") == 0) {
		dir = params_get(ps, "d");
		wikinew(dir);
	} else if (strcmp(ps->params[0].key, "newform") == 0) {
		wikinewform();
	} else if (strcmp(ps->params[0].key, "delete") == 0) {
		page = params_get(ps, "p");
		dir = params_get(ps, "d");
		wikidelete(dir, page);
	} else if (strcmp(ps->params[0].key, "test") == 0) {
		testpage();
	}
	params_free(ps);
	return EXIT_SUCCESS;
}
