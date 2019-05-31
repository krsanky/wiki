#include <unistd.h>
#include <mtemplate.h>
#include <assert.h>

#include "wiki.h"

int
sort_mdict(struct mobject *dict)
{
	struct miterator *iter;
	struct miteritem *item;

	char		buf[100];
	char		buf2[100];
	size_t		l;

	assert((iter = mobject_getiter(dict)) != NULL);

	while ((item = miterator_next(iter)) != NULL) {
		mobject_to_string(item->key, buf, 100-1);
		mobject_to_string(item->value, buf2, 100-1);
		printf("key:%s value:\n", buf);

	}
	l = mdict_len(dict);
	printf("dict len:%zu\n", l);
	printf("NOW peel off the items and sort them with a RB_TREE\n");

	return 0;
}

