#include "myhtml.h"

void
myhtml_header()
{
	printf("\
<!doctype html>\
<html>\
<head>\
<title>wiki</title>\
</head>\
<body>\
\n");
}

void
myhtml_footer()
{
	printf("\
</body>\
</html>\
\n");
}

void
myhtml_topnav()
{
	printf("<a href=\"/\">home</a> ");
	printf("<a href='/wiki.cgi?index'>index</a> ");
	/* printf("<a href='/edit.cgi?asd=123'>edit</a> "); */
	printf("\n");
}
