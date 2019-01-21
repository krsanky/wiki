#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int	arr[]  = {1, -1, 123, 0, 4, -23};

int
my_int_compare(const void *p, const void *q)
{
	int x = *(const int *)p;
	int y = *(const int *)q;

	if (x < y)
		return -1;
	if (x > y)
		return 1;
	return 0;
}

int
main()
{
	int		arrl = sizeof(arr) / sizeof(arr[0]);

	printf("test_sort...\n");
	printf("NOT sorted:\n");
	for (int i=0; i<arrl; i++) 
		printf("i[%d]: %d\n", i, arr[i]);
	
	qsort(arr, arrl, sizeof(1), &my_int_compare);
	printf("SORTED:\n");
	for (int i=0; i<arrl; i++) 
		printf("i[%d]: %d\n", i, arr[i]);
	
	return EXIT_SUCCESS;
}
