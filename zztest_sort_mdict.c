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

void
print_mdict(struct mobject *d)
{
	struct miterator *iter;
	struct miteritem *item;
	char 		buf      [256];
	char 		buf2     [256];

	printf("---dict->type:%d\n", mobject_type(d));
	assert(mobject_type(d) == TYPE_MDICT);
	assert((iter = mobject_getiter(d)) != NULL);
	while ((item = miterator_next(iter)) != NULL) {
		mobject_to_string(item->key, buf, 256-1);
		mobject_to_string(item->value, buf2, 256-1);
		printf("k:%s v:%s\n", buf, buf2);	
	}
}

int
main()
{
	struct mobject	*d;

	assert((d = mdict_new()) != NULL);
	mdict_insert_ss(d, "de->d_name", "anchor");
	mdict_insert_ss(d, "BWQA", "asdas qweqw");
	mdict_insert_ss(d, "qweqwe", "123asd");
	mdict_insert_ss(d, "vdessqwq", "asdas qweqw");
	mdict_insert_ss(d, "ANC", "asdas qweqw");
	print_mdict(d);

	d = sort_mdict(d);
	printf("------------\n");
	print_mdict(d);

	return EXIT_SUCCESS;
}

