#include <stdlib.h>
#include <string.h>
#include <mtemplate.h>
#include <assert.h>
#include <sys/tree.h>

#include "wiki.h"

#include "sort_mdict.h"

/* ------------- RB ------------ */
struct myitem {
	RB_ENTRY(myitem) entry;
	char           *key;
	char           *val;
};

int
myitem_cmp(struct myitem * i1, struct myitem * i2)
{
	return strcmp(i1->key, i2->key);
}

RB_HEAD(myitem_tree, myitem) head = RB_INITIALIZER(&head);
RB_PROTOTYPE(myitem_tree, myitem, entry, myitem_cmp)
RB_GENERATE(myitem_tree, myitem, entry, myitem_cmp)
/* ------------- /RB ----------- */

	void
			mdict_to_tree ()
{

}

int
sort_mdict(struct mobject * dict)
{
	struct miterator *iter;
	struct miteritem *item;
	char 		buf      [256];
	char 		buf2     [256];
	struct myitem  *n;
	size_t 		ks    , vs;

	assert((iter = mobject_getiter(dict)) != NULL);
	while ((item = miterator_next(iter)) != NULL) {
		mobject_to_string(item->key, buf, 100 - 1);
		mobject_to_string(item->value, buf2, 100 - 1);
		printf("key:%s value:\n", buf);


		n = calloc(1, sizeof(struct myitem));
		assert(n != NULL);

		ks = mstring_len(item->key);
		vs = mstring_len(item->value);
		n->key = malloc(ks);
		n->val = malloc(vs);
		assert((n->key != NULL) && (n->val != NULL));

		mobject_to_string(item->key, n->key, ks);
		mobject_to_string(item->value, n->val, vs);

		RB_INSERT(myitem_tree, &head, n);

	}
	return 0;

}
int
zzsort_mdict(struct mobject * dict)
{
	struct miterator *iter;
	struct miteritem *item;

	char 		buf      [100];
	char 		buf2     [100];
	size_t 		l;

	assert((iter = mobject_getiter(dict)) != NULL);

	while ((item = miterator_next(iter)) != NULL) {
		mobject_to_string(item->key, buf, 100 - 1);
		mobject_to_string(item->value, buf2, 100 - 1);
		printf("key:%s value:\n", buf);

	}
	l = mdict_len(dict);
	printf("dict len:%zu\n", l);
	printf("NOW peel off the items and sort them with a RB_TREE\n");

	return 0;
}
