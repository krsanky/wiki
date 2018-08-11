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
	char	*qs;

	qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	nlog("QUERY_STRING:%s", qs);
	msgpage("asd");

	/*
	if ((strlen(qs) < 1) || (p < 1)) {
		mainpage();
	}
	else if (strcmp(params[0].key, "start") == 0) {
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
		wikiindex(get_param("d", params, NUM_HTTP_PARAMS));
	} else if (strcmp(params[0].key, "view") == 0) {
		param = get_param("p", params, NUM_HTTP_PARAMS);
		if (param != NULL)
			wikiview(get_param("d", params, NUM_HTTP_PARAMS), param);
		else
			errpage("param p (page) not found");
	} else if (strcmp(params[0].key, "edit") == 0) {
		page = get_param("p", params, NUM_HTTP_PARAMS);
		dir = get_param("d", params, NUM_HTTP_PARAMS);
		wikiedit(dir, page);
	} else if (strcmp(params[0].key, "new") == 0) {
		page = get_param("p", params, NUM_HTTP_PARAMS);
		dir = get_param("d", params, NUM_HTTP_PARAMS);
		wikinew(dir, page);
	} else if (strcmp(params[0].key, "editform") == 0) {
		wikieditform();
	}
	*/

	return EXIT_SUCCESS;
}
