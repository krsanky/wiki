#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wiki.h"
#include "myhtml.h"
#include "yuarel.h"


int
main(void)
{
	struct yuarel_param *params;
	int 		p;
	char           *msg;
	char           *val;
	char           *qs;
	int 		ret;

	params = malloc(sizeof(*params) * 10);
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
		p = yuarel_parse_query(qs, '&', params, 10);
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
		wikiindex();
	} else if (strcmp(params[0].key, "view") == 0) {
		ret = nlog("nlog nlog nlog:%s %d", "..this is the var...", 42);
		get_param("p", params, 10);
		wikiview("m1.md");
	} else {		/* unreachable ? */
		query_params_test(params, 10);
	}

	return EXIT_SUCCESS;
}
