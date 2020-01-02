#include <stdlib.h>
#include <string.h>
#include <mtemplate.h>
#include <assert.h>
#include <sys/tree.h>

#include "wiki.h"

#include "sort_mdict.h"

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

/* "head" is a global  ... rename to sort_mdict_head ? */
RB_HEAD(myitem_tree, myitem) head = RB_INITIALIZER(&head);
RB_PROTOTYPE(myitem_tree, myitem, entry, myitem_cmp)
RB_GENERATE(myitem_tree, myitem, entry, myitem_cmp)

struct mobject *
sort_mdict(struct mobject * dict)
{
	struct miterator *iter;
	struct miteritem *item;
	char 		buf      [256];
	char 		buf2     [256];
	struct myitem  *n, *var, *nxt;
	size_t 		ks    , vs;

	printf("dict->type:%d\n", mobject_type(dict));
	assert(mobject_type(dict) == TYPE_MDICT);

	assert((iter = mobject_getiter(dict)) != NULL);
	while ((item = miterator_next(iter)) != NULL) {
		mobject_to_string(item->key, buf, 100 - 1);
		mobject_to_string(item->value, buf2, 100 - 1);

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
	miterator_free(iter);
	mobject_free(dict);

	assert((dict = mdict_new()) != NULL);
	n = NULL;
	RB_FOREACH(n, myitem_tree, &head) {
		mdict_insert_ss(dict, n->key, n->val);
	}
	printf("dict->type(after):%d\n", mobject_type(dict));

	/* clean up the RB tree */
	assert(RB_EMPTY(&head) != 1);
	nxt = NULL;
	for (var = RB_MIN(myitem_tree, &head); var != NULL; var = nxt) {
		nxt = RB_NEXT(myitem_tree, &head, var);
		RB_REMOVE(myitem_tree, &head, var);
		free(var);
	}
	assert(RB_EMPTY(&head) == 1);

	return dict;
}



