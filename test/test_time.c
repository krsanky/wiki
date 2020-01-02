#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void
set_cookie(char *n, char *v)
{
	time_t 		now   , future;
	struct tm      *tm_info;
	char 		buf      [256];
	const unsigned long year = 60 * 60 * 24 * 356;

	time(&now);
	future = year + now;
	tm_info = localtime(&future);
	strftime(buf, 256, "%a, %d %b %Y %H:%M:%S GMT", tm_info);

	printf("Set-Cookie: %s=%s; Secure; HttpOnly; Expires=%s\r\n", n, v, buf);

	/*
	Expires=Wed, 21 Oct 2015 07:28:00 GMT
	
	Date: <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT
	
	One of "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", or "Sun" (case-sensitive).
	<day>
	    2 digit day number, e.g. "04" or "23".
	
	Date: Wed, 21 Oct 2015 07:28:00 GMT
	*/
}

int
main()
{
	time_t 		timer , future;
	char 		buf      [256];
	struct tm      *tm_info;
	unsigned long 	year;

	year = 60 * 60 * 24 * 356;
	printf("a year is %lu secs\n", year);

	time(&timer);
	printf("time_t time:%lld\n", timer);

	future = year + timer;


	tm_info = localtime(&timer);
	strftime(buf, 256, "%Y-%m-%d %H:%M:%S", tm_info);
	printf("now:         %s\n", buf);

	tm_info = localtime(&future);
	strftime(buf, 256, " %a %Y-%m-%d %H:%M:%S", tm_info);
	printf("1-year-away: %s\n", buf);

	set_cookie("name123", "vasdqwd,12..");

	return EXIT_SUCCESS;
}
