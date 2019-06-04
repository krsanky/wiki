#include <stdio.h>
#include <dirent.h>
#include <sys/tree.h>
#include <string.h>

#include "wiki_file_io.h"

struct sortitem {
	RB_ENTRY(sortitem) entry;
	char	*name;
};
int
sortitem_cmp(struct sortitem * x, struct sortitem * y)
{
	return strcmp(x->name, y->name);
}

RB_HEAD(sorttree, sortitem) head = RB_INITIALIZER(&head);
RB_PROTOTYPE(sorttree, sortitem, entry, sortitem_cmp)
RB_GENERATE(sorttree, sortitem, entry, sortitem_cmp)

int
make_sorted_dir_arr(char *dir, char **list)
{
	DIR            *d;
	struct dirent  *de;

	d = opendir(dir);
	if (d == NULL) {
		printf("could not open dir:%s", dir);
		return -1;
	}

	while ((de = readdir(d)) != NULL) {
		if (de->d_name[0] != '.') {
			if (de->d_type == DT_DIR) {
				//mdict_insert_ss(dirs, de->d_name, anchor);
				printf("d:%s len:%d\n", de->d_name, strlen(de->d_name));
			} 
		}
	}

	return 0;
}


