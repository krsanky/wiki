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
	printf("\
<a href=\"/\">home</a> <a href='/edit.cgi?asd=123'>edit</a>\n");
}

