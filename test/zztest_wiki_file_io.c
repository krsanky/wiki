#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "wiki_file_io.h"

void
test_make_sorted_dir_arr()
{
	int	len, i;
	char	d[] = "/home/wise";
	char	**list;
	list = NULL;

	len = 999;	
	list = make_sorted_dir_arr(d, &len);
	printf("len:%d\n", len);

	for (i=0; i<len; i++)
		printf("%s\n", list[i]);

	free_sorted_arr(list, len);
}

int
main()
{
	test_make_sorted_dir_arr();
	return EXIT_SUCCESS;
}

