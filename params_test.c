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
	PARAM          *params;
	char           *query;
	int 		ret;
	char           *tmp;

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

void
ret_mal_str(char **s)
{
	char           *s1;
	char           *cs = "MALLOC STRING";

	s1 = malloc(strlen(cs) + 1);
	if (s1 == NULL)
		return;
	strlcpy(s1, cs, strlen(cs) + 1);
	*s = s1;
}

void
pointer_malloc_str_test()
{
	char           *ms;
	ret_mal_str(&ms);
	printf("ms:%s\n", ms);
	free(ms);
}

void
f1(int a)
{
	printf("A:%d\n", a);
}

void 
ptr_func_test()
{
	printf("ptr_func_test()...\n");
	void            (*fun_ptr) (int);
	fun_ptr = &f1;
	(*fun_ptr) (10);
}

int
test_POST(char *b, char *f)
{
	char           *buf = NULL;
	int 		ret;

	ret = my_read_file(f, &buf);
	if (buf != NULL) {
		/* printf("ofile:\n%s\n", buf); */
	} else {
		printf("buf == NULL\n");
		return -1;
	}

	PARAM          *params;
	int		nump = 10;
	params = malloc(sizeof(PARAM) * nump);
	params_initialize(params, nump);
	 
	params_parse_multipart_POST(buf, b, params, nump);

	params_free(params, nump);
	free(buf);
	return 0;
}

int
main(int argc, char **argv)
{
	char		*b1 = "----WebKitFormBoundary4I8D3cAgAWb1bauA";
	char		*f1 = "tmpPOST123.txt";

	/*
	char           *b, *f;
	if (argc < 3) {
		printf("%s <boundary-str> <file>\n", argv[0]);
		return EXIT_FAILURE;
	} 
	b = argv[1];
	f = argv[2];
	*/

	printf("test_POST(%s, %s): %d\n", b1, f1, test_POST(b1, f1));
	/*
	printf("test_url_params(): %d\n", test_url_params(NULL));
	ptr_func_test();
	pointer_malloc_str_test();
	*/

	return EXIT_SUCCESS;
}


