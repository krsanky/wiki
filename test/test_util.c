#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <dirent.h>

#include "util.h"

int
main()
{
	int 		ret;
	char           *buf;

	printf("hey!\n");
	ret = cat_strings(&buf, 2, "asd..", "qwe..");
	printf("ret:%d num:2 buf:%s\n", ret, buf);
	free(buf);

	ret = cat_strings(&buf, 1, "asd..");
	printf("ret:%d num:1 buf:%s\n", ret, buf);
	free(buf);

	return 0;
}
