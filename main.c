#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "myhtml.h"
#include "yuarel.h"
#include "wiki.h"

#include "settings.h"
#include "util.h"


int
main(void)
{
	struct yuarel_param *params;
	int 		p;
	char           *msg;
	char           *val;
	char           *qs;
	int 		ret;
	char           *param;
	char           *page;
	char           *dir;

	params = malloc(sizeof(*params) * NUM_HTTP_PARAMS);
	if (params == NULL) {
		puts("error with malloc");
		return EXIT_FAILURE;
	}
	qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	if (strlen(qs) > 0) {
		p = yuarel_parse_query(qs, '&', params, NUM_HTTP_PARAMS);
		if (p < 0) {
			char           *tmpstr = malloc(100);
			if (tmpstr == NULL) {
				errpage("error with yuarel_parse_query()");
			} else {
				snprintf(tmpstr, 99, "error with yuarel_parse_query() [QUERY_STRING:%s][len:%lu]", qs, strlen(qs));
				errpage(tmpstr);
				free(tmpstr);
			}
			return EXIT_FAILURE;
		}
	}
	if ((strlen(qs) < 1) || (p < 1)) {
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
	} else {		/* unreachable ? */
		query_params_test(params, NUM_HTTP_PARAMS);
	}

	return EXIT_SUCCESS;
}
