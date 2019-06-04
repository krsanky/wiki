#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "wiki_file_io.h"

int
main()
{
	int	ret;
	char	d[] = "/home/wise";
	char	**list;
	list = NULL;

	ret = make_sorted_dir_arr(d, list);
	return EXIT_SUCCESS;
}

