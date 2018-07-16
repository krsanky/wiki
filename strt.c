#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct yuarel_param {
	char *key;
	char *val;
};

void 
fn1(struct yuarel_param params[], size_t sz)
{
	printf("i am fn1\n");
}

int 
main(void)
{
	printf("test\n");
	struct yuarel_param params[10];

	fn1(params, sizeof(params)/sizeof(*params));
	printf("sz params:%lu sz*params:%lu\n", sizeof(params),sizeof(*params));

	return 0;
}

