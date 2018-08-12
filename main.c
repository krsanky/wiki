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
	char		*qs;
	PARAM		*params;
	char		*param;
	char		*page;
	char		*dir;
	char		*val;
	char		*msg;
	int		ret;

	qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	nlog("QUERY_STRING:%s", qs);

	params = malloc(sizeof(PARAM) * NUM_HTTP_PARAMS);
	params_initialize(params, NUM_HTTP_PARAMS);
	params_parse_query(qs, params, NUM_HTTP_PARAMS);

	if (strlen(qs) < 1) {
		mainpage();
	} else if (strcmp(params[0].key, "start") == 0) {
		msgpage("start");
	} else if (strcmp(params[0].key, "logtest") == 0) {
		if (params[0].val != NULL)
			val = params[0].val;
		else
			val = "NO VALUE";
		msg = "logtest";
		if (params[0].val != NULL) {
			msg = params[0].val;
		}
		if ((ret = wikilog(val)) < 0) {
			errpage(msg);
		} else {
			msgpage(msg);
		}
	} else if (strcmp(params[0].key, "index") == 0) {
		wikiindex(params_get("d", params, NUM_HTTP_PARAMS));
	} else if (strcmp(params[0].key, "view") == 0) {
		param = params_get("p", params, NUM_HTTP_PARAMS);
		if (param != NULL)
			wikiview(params_get("d", params, NUM_HTTP_PARAMS), param);
		else
			errpage("param p (page) not found");
	} else if (strcmp(params[0].key, "edit") == 0) {
		page = params_get("p", params, NUM_HTTP_PARAMS);
		dir = params_get("d", params, NUM_HTTP_PARAMS);
		wikiedit(dir, page);
	} else if (strcmp(params[0].key, "new") == 0) {
		page = params_get("p", params, NUM_HTTP_PARAMS);
		dir = params_get("d", params, NUM_HTTP_PARAMS);
		wikinew(dir, page);
	} else if (strcmp(params[0].key, "editform") == 0) {
		wikieditform();
	}

	params_free(params, NUM_HTTP_PARAMS);
	return EXIT_SUCCESS;
}
