#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
void
qsort(void *base, size_t nmemb, size_t size,
int (*compar)(const void *, const void *));
*/

int
flist_cmp(const void *p1, const void *p2)
{
/*
	const struct flist *f1 = p1, *f2 = p2;

	return strcmp(f1->wpath, f2->wpath);
*/
	return 0;
}

void
flist_fixup(const struct opts * opts, struct flist * fl, size_t * sz)
{
	size_t 		i;

	/*qsort(fl, *sz, sizeof(struct flist), flist_cmp);*/
	qsort(fl, *sz, 0, flist_cmp);

	for (i = 0; i < *sz - 1; i++) {
		/*if (strcmp(fl[i].path, fl[i + 1].path))*/
		if (strcmp("asd", "qwe"))
			continue;
		/*
		WARNX(opts, "duplicate path: %s", fl[i + 1].path);
		 TODO. */
	}
}

int
main()
{
	printf("test_sort...\n");
	return EXIT_SUCCESS;
}
