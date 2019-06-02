#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <mtemplate.h>

#include "sort_mdict.h"

struct mys {
	int	a;
	int	b;
};

/**
 * This shows that ...
 */
void
f1(struct mys *x)
{
	x->a = -12;
	x->b = -42;
	printf("a:%d b:%d\n", x->a, x->b);
}

void
test1()
{
	struct mys	*m1;
	
	assert((m1 = calloc(1, sizeof(struct mys))) != NULL);
	m1->a = 20;
	m1->b = 50;
	printf("a:%d b:%d\n", m1->a, m1->b);	
	f1(m1);
	printf("a:%d b:%d\n", m1->a, m1->b);	
}

int
main()
{
	struct mobject	*d;
	int	ret;

	assert((d = mdict_new()) != NULL);
	mdict_insert_ss(d, "de->d_name", "anchor");
	mdict_insert_ss(d, "BWQA", "asdas qweqw");
	mdict_insert_ss(d, "qweqwe", "123asd");
	mdict_insert_ss(d, "vdessqwq", "asdas qweqw");
	mdict_insert_ss(d, "ANC", "asdas qweqw");

	ret = sort_mdict(d);

	return EXIT_SUCCESS;
}

