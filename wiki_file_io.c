#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/tree.h>
#include <string.h>

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

char **
make_sorted_dir_arr(char *dir, int *length)
{
	DIR            *d;
	struct dirent  *de;
	struct sortitem *si, *nxt;
	int		len, i;
	char		*tmpstr;
	char		**list;
	

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
/* 	printf("len:%d malloc-size:%lu\n", len, len*sizeof(char*)); */

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
