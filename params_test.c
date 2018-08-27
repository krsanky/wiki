#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "params.h"
#include "settings.h"

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
read_file(char *f, char **buf)
{
	FILE	       *pfile;
	long		numbytes;
	char		*buf;

	if (f == NULL)
		f = "test/post_data_1.txt";
	if ((pfile = fopen(f, "r")) == NULL) 
		exit_err("error opening file");
	fseek(pfile, 0L, SEEK_END);
	numbytes = ftell(pfile);
	printf("num bytes:%ld\n", numbytes);

	/* reset */
	fseek(pfile, 0L, SEEK_SET);

	buf = malloc(numbytes); /* +1 ? */
	if (buf == NULL) exit_err("malloc");

	fread(buf, 1, numbytes, pfile);
	printf("file:\n%s\n", buf);

	free(buf);
	if (pfile != NULL)
		fclose(pfile);
	return 0;
}

int
test_POST(char *f)
{
//params_parse_multipart_POST(char * text, char * boundary, PARAM * params, int max_params)
}

int
main(int argc, char **argv)
{
	char		*argv1 = NULL;

	printf("-------------%s argc:%d-------------\n", argv[0], argc);
	if (argc > 1)
		argv1 = argv[1];
		

	/*
	 * printf("test_url_params(): %d\n", test_url_params(NULL));
	 */
	printf("test_POST(%s): %d\n", argv1, test_POST(argv1));

	return EXIT_SUCCESS;
}
