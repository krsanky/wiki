/*
 * Copyright (c) 2019 Paul Wisehart paul@oldcode.org
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/tree.h>
#include <string.h>

#include "util.h"

#include "wiki_file_io.h"

struct sortitem {
	RB_ENTRY(sortitem) entry;
	char           *name;
};

int
sortitem_cmp(struct sortitem * x, struct sortitem * y)
{
	return strcmp(x->name, y->name);
}

RB_HEAD(sorttree, sortitem) head = RB_INITIALIZER(&head);
RB_PROTOTYPE(sorttree, sortitem, entry, sortitem_cmp)
RB_GENERATE(sorttree, sortitem, entry, sortitem_cmp)

char          **
make_sorted_dir_arr(char *dir, int *length)
{
	DIR            *d;
	struct dirent  *de;
	struct sortitem *si, *nxt;
	int 		len      , i;
	char           *tmpstr;
	char          **list;


	d = opendir(dir);
	if (d == NULL) {
		printf("could not open dir:%s", dir);
		return NULL;
	}
	while ((de = readdir(d)) != NULL) {
		if (de->d_name[0] != '.') {
			if (de->d_type == DT_DIR) {
				//printf("d:%s len:%lu\n", de->d_name, strlen(de->d_name));
				//printf("sizeof1:%lu sizeof2:%lu\n", sizeof(struct sortitem), sizeof(*si));
				si = malloc(sizeof(*si));
				assert(si != NULL);
				si->name = strdup(de->d_name);
				assert(si->name != NULL);
				RB_INSERT(sorttree, &head, si);
			}
		}
	}

	si = NULL;
	len = 0;
	RB_FOREACH(si, sorttree, &head) {
		//printf("%s\n", si->name);
		len++;
	}
	/* printf("len:%d malloc-size:%lu\n", len, len*sizeof(char*)); */

	list = malloc(len * sizeof(char *));
	assert(list != NULL);
	i = 0;
	RB_FOREACH(si, sorttree, &head) {
		tmpstr = strdup(si->name);
		assert(tmpstr != NULL);
		list[i] = tmpstr;
		i++;
	}


	/* clean up the RB tree */
	si = NULL;
	for (si = RB_MIN(sorttree, &head); si != NULL; si = nxt) {
		nxt = RB_NEXT(sorttree, &head, si);
		RB_REMOVE(sorttree, &head, si);
		free(si);
	}
	assert(RB_EMPTY(&head) == 1);
	/*
		for (i=0; i<len; i++)
			printf("%s\n", list[i]);
	*/

	*length = len;
	return list;
}

char          **
make_sorted_page_arr(char *dir, int *length)
{
	DIR            *d;
	struct dirent  *de;
	struct sortitem *si, *nxt;
	int 		len      , i;
	char           *tmpstr;
	char          **list;

	d = opendir(dir);
	if (d == NULL) {
		printf("could not open dir:%s", dir);
		return NULL;
	}
	while ((de = readdir(d)) != NULL) {
		if (is_wiki_file(de)) {
			si = malloc(sizeof(*si));
			assert(si != NULL);
			si->name = strdup(de->d_name);
			assert(si->name != NULL);
			RB_INSERT(sorttree, &head, si);
		}
	}

	si = NULL;
	len = 0;
	RB_FOREACH(si, sorttree, &head) {
		//printf("%s\n", si->name);
		len++;
	}
	nlog("140 len:%d malloc-size:%lu\n", len, len * sizeof(char *));
	if (len == 0) {
		return NULL;
	}
	list = malloc(len * sizeof(char *));
	assert(list != NULL);
	i = 0;
	RB_FOREACH(si, sorttree, &head) {
		tmpstr = strdup(si->name);
		assert(tmpstr != NULL);
		list[i] = tmpstr;
		i++;
	}


	/* clean up the RB tree */
	assert(RB_EMPTY(&head) != 1);
	si = NULL;
	for (si = RB_MIN(sorttree, &head); si != NULL; si = nxt) {
		nxt = RB_NEXT(sorttree, &head, si);
		RB_REMOVE(sorttree, &head, si);
		free(si);
	}
	assert(RB_EMPTY(&head) == 1);
	/*
		for (i=0; i<len; i++)
			printf("%s\n", list[i]);
	*/

	*length = len;
	return list;
}

void
free_sorted_arr(char **list, int l)
{
	int 		i;
	for (i = 0; i < l; i++) {
		free(list[i]);
	}
	free(list);
}
