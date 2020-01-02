#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "params.h"

int
main()
{
	char           *qs = "index&asd=123&qweqwe=zxcasd123";
	char           *qs2 = "page=qwd123123.md&dir=OpenBSD%2Fdir123";
	char           *qs3 = "page=qwd1.md&dir=dev%2Flang";
	PARAMS         *ps;
	int 		nparams = 10;
	char           *p1;
	int 		ret;
	char           *decode;

	printf("test_params\n");

	ps = params_create(nparams, qs2);

	p1 = params_get(ps, "123asddir");
	printf("p1:%s\n", p1);

	p1 = params_get(ps, "dir");
	printf("p1:%s\n", p1);
	decode = malloc(strlen(p1) + 1);
	if (decode == NULL) {
		printf("malloc error\n");
		return EXIT_FAILURE;
	}
	ret = params_urldecode(p1, decode);
	printf("params_urldecode: ret:%d decode:%s\n", ret, decode);

	char           *s1 = "asd  123  qwe";
	char           *s2 = "asd/123/qwe";
	char           *p2;
	p2 = malloc(strlen(s1) + 1);
	if (p2 == NULL) {
		printf("malloc error");
		return EXIT_FAILURE;
	}
	ret = strlcpy(p2, s1, strlen(s1) + 1);
	printf("ret:%d sizeof\&:%d sizeof:%d p2[%s] s1[%s]\n", ret, sizeof(&p2), sizeof(p2), p2, s1);


	params_free(ps);
	return EXIT_SUCCESS;
}
