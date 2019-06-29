#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main()
{
	time_t 		timer, future;
	char 		buf      [256];
	struct tm      *tm_info;
	unsigned long	year;


	year = 60 * 60 * 24 * 356;
	printf("a year is %lu secs\n", year);

	time(&timer);
	printf("time_t time:%lld\n", timer);

	future = year + timer;



	

	tm_info = localtime(&timer);
	strftime(buf, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf("now:         %s\n", buf);

	tm_info = localtime(&future);
	strftime(buf, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	printf("1-year-away: %s\n", buf);

	return EXIT_SUCCESS;
}
