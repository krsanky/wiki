#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main()
{
	printf("time\n");

	time_t 		timer;
	char 		buf      [256];
	struct tm      *tm_info;

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buf, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf("%s\n", buf);

	return EXIT_SUCCESS;
}
