#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"
#include "settings.h"

int
main(int argc, char **argv)
{
	PARAM          *params;
	char           *query;
	int 		ret;
	char           *tmp;

	params = malloc(sizeof(PARAM) * NUM_HTTP_PARAMS);
	params_initialize(params, NUM_HTTP_PARAMS);

	printf("%s argc:%d\n", argv[0], argc);

	if (argc > 1) {
		query = argv[1];
	} else {
		query = "noval&default=123123&querquer=123asd";
	}

	ret = params_parse_query(query, params, NUM_HTTP_PARAMS);
	for (int i = 0; i < NUM_HTTP_PARAMS; i++) {
		printf("param[%d] k:%s v:%s\n", i, params[i].key, params[i].val);
	}

	tmp = params_get("default", params, NUM_HTTP_PARAMS);
	printf("params_get:%s\n", tmp);
	tmp = params_get("123asddefault", params, NUM_HTTP_PARAMS);
	printf("params_get:%s\n", tmp);

	params_free(params, NUM_HTTP_PARAMS);
	return EXIT_SUCCESS;
}
