#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "mtemplate.h"

#include "wiki.h"

int
main()
{
	struct miterator *iter;
	struct miteritem *item;
	struct mobject *data;
	struct mobject *pages;
	struct mobject *sorted;
	int 		ret;
	char		buf[100];
	char		buf2[100];
	size_t		l;

	chdir("../htdocs");
	ret = make_mobject_dirlist("/", &data);
	/* pages dirs */
	printf("ret:%d\n", ret);
	pages = mdict_item_s(data, "pages");

	/*
			if ((iter = mobject_getiter(o)) == NULL) {
				mobject_free(new_obj);
				return NULL;
			}
			while ((item = miterator_next(iter)) != NULL) {
				if ((k = mobject_deepcopy(item->key)) == NULL) {
	 mdict_deepcopy_err:
					mobject_free(new_obj);
					miterator_free(iter);
					return NULL;
				}
				if ((v = mobject_deepcopy(item->value)) == NULL) {
					mobject_free(k);
					goto mdict_deepcopy_err;
				}
				if (mdict_insert(new_obj, k, v) != 0) {
					mobject_free(k);
					mobject_free(v);
					goto mdict_deepcopy_err;
				}
			}
			miterator_free(iter);

	*/

	if ((sorted = mdict_new()) == NULL) {
		printf("error mdict_new()\n");
		return EXIT_FAILURE;
	}
	if ((iter = mobject_getiter(pages)) == NULL) {
		printf("error getting miterator\n");
		return EXIT_FAILURE;
	}

	while ((item = miterator_next(iter)) != NULL) {
		
		mobject_to_string(item->key, buf, 100-1);
		mobject_to_string(item->value, buf2, 100-1);
		printf("key:%s value:\n", buf);

	}
	l = mdict_len(pages);
	printf("pages len:%zu\n", l);


	return EXIT_SUCCESS;
}


/*
struct mobject *
mdict_remove_s(struct mobject *dict, const char *key)
{
	struct mobject *tmp;
	struct mobject *r;

	if ((tmp = mstring_new(key)) == NULL)
		return NULL;
	r = mdict_remove(dict, tmp);
	mobject_free(tmp);
	return r;
}
*/
/*
TAILQ_HEAD(mdict_entries, mdict_entry);
*/
/*
A TAILQ_HEAD structure is declared as follows:

   TAILQ_HEAD(HEADNAME, TYPE) head;

where HEADNAME is the name of the structure to be defined, and
struct TYPE is the type of the elements to be linked into the
tail queue.  A pointer to the head of the tail queue can later
be declared as:

   struct HEADNAME *headp;

(The names head and headp are user selectable.)
*/

/* *********************
struct mobject *
mdict_remove(struct mobject *_dict, const struct mobject *key)
{
	struct mdict *dict = (struct mdict *)_dict;
	struct mdict_entry *e;
	struct mobject *ret;

	if (dict->type != TYPE_MDICT || key->type != TYPE_MSTRING)
		return NULL;
	TAILQ_FOREACH(e, &dict->entries, entry) {
		if (mstring_cmp(e->key, key) == 0) {
			TAILQ_REMOVE(&dict->entries, e, entry);
			ret = e->value;
			mobject_free((struct mobject *)e->key);
			bzero(e, sizeof(*e));
			free(e);
			dict->num_entries--;
			return ret;
		}
	}
	return NULL;
}

int
mdict_delete(struct mobject *_dict, const struct mobject *key)
{
	struct mdict *dict = (struct mdict *)_dict;
	struct mobject *o;

	if (dict->type != TYPE_MDICT || key->type != TYPE_MSTRING)
		return -1;
	if ((o = mdict_remove(_dict, key)) == NULL)
		return -1;
	mobject_free(o);
	dict->num_entries--;
	return 0;
}

int
mdict_insert(struct mobject *_dict, struct mobject *key,
    struct mobject *value)
{
	struct mdict *dict = (struct mdict *)_dict;
	struct mdict_entry *e;

	if (dict->type != TYPE_MDICT || key->type != TYPE_MSTRING)
		return -1;
	TAILQ_FOREACH(e, &dict->entries, entry) {
		if (mstring_cmp(e->key, key) == 0)
			return -1;
	}
	if ((e = calloc(1, sizeof(*e))) == NULL)
		return -1;
	e->key = key;
	e->value = value;
	TAILQ_INSERT_TAIL(&dict->entries, e, entry);
	dict->num_entries++;
	return 0;
}

int
mdict_replace(struct mobject *_dict, struct mobject *key,
    struct mobject *value)
{
	struct mdict *dict = (struct mdict *)_dict;
	struct mdict_entry *e;

	if (dict->type != TYPE_MDICT || key->type != TYPE_MSTRING)
		return -1;
	TAILQ_FOREACH(e, &dict->entries, entry) {
		if (mstring_cmp(e->key, key) == 0)
			break;
	}
	if (e != TAILQ_END(&dict->entries)) {
		TAILQ_REMOVE(&dict->entries, e, entry);
		mobject_free((struct mobject *)e->key);
		mobject_free(e->value);
		dict->num_entries--;
	} else {
		if ((e = calloc(1, sizeof(*e))) == NULL)
			return -1;
	}
	e->key = key;
	e->value = value;
	TAILQ_INSERT_TAIL(&dict->entries, e, entry);
	dict->num_entries++;
	return 0;
}

size_t
mdict_len(const struct mobject *_dict)
{
	struct mdict *dict = (struct mdict *)_dict;

	if (dict->type != TYPE_MDICT)
		return 0;
	return dict->num_entries;
}


*/
