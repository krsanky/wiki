#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"
#include "settings.h"
#include "util.h"

void
exit_err(char *msg)
{
	printf("err:%s\n", msg);
	exit(1);
}

int
test_url_params(char *arg)
{
	PARAM	       *params;
	char	       *query;
	int		ret;
	char	       *tmp;

	params = malloc(sizeof(PARAM) * NUM_HTTP_PARAMS);
	params_initialize(params, NUM_HTTP_PARAMS);


	if (arg != NULL) {
		query = arg;
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

	return ret;
}

int
test_POST(char *f)
{
	char	       *buf = NULL;
	int		ret;

	ret = my_read_file(f, &buf);
	if (buf != NULL) {
		printf("ofile:\n%s\n", buf);
	} else {
		printf("buf == NULL\n");
		return -1;
	}



	/*params_parse_multipart_POST(buf, boundary, PARAM * params, int max_params)*/

	free(buf);
	return 0;
}

void
ret_mal_str(char **s)
{
	char		*s1;
	char		*cs = "MALLOC STRING";

	s1 = malloc(strlen(cs)+1);
	if (s1 == NULL) return;
	strlcpy(s1, cs, strlen(cs)+1);
	*s = s1;
}

void
f1(int a)
{
	printf("A:%d\n", a);
}

int
main(int argc, char **argv)
{
	char	       *argv1 = NULL;
	char		*f = "test/post_data_1.txt";

	printf("::-----------%s argc:%d-------------\n", argv[0], argc);
	if (argc > 1)
		argv1 = argv[1];
	else
		argv1 = f;

	/*
	printf("test_url_params(): %d\n", test_url_params(NULL));
	*/
	printf("test_POST(%s): %d\n", argv1, test_POST(argv1));

	void (*fun_ptr)(int);
	fun_ptr = &f1;
	(*fun_ptr)(10);

	char	*ms;
	ret_mal_str(&ms);
	printf("ms:%s\n", ms);
	free(ms);

	return EXIT_SUCCESS;
}
