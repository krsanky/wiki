#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "util.h"

int
main()
{
	int 		ret;
	char           *buf;

	printf("hey!\n");
	ret = cat_strings(&buf, 2, "asd..", "qwe..");
	printf("buf:%s\n", buf);

	free(buf);
	return 0;
}
