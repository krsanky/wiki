#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "myhtml.h"

void
myhtml_header()
{
	printf("\
<!doctype html>\n\
<html>\n\
<head><meta charset='utf-8'>\
<meta name='viewport' content='width=device-width, initial-scale=1'>\
<head>\
<title>oldcode wiki</title>\
<style type='text/css'>\
body{margin:40px auto;max-width:80%%;line-height:1.6;font-size:18px;color:#444; padding:0 10px}\
h1,h2,h3{line-height:1.2}\
</style>\
</head>\n\
<body>\n\
<header><h1>Oldcode Wiki</h1></header>\
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
	printf("<hr/>\n");
	printf("<a href=\"/\">home</a> ");
	printf("<a href='/wiki.cgi?index'>index</a>\n");
	/* printf("<a href='/edit.cgi?asd=123'>edit</a> "); */
	printf("<hr/>\n");
}

void
myhtml_breadcrumbs(char *dir, char *page)
{
	char           *str = NULL;
	char           *dir_;
	char           *dir2;

	printf("/");

	if (dir != NULL) {
		dir_ = malloc(strlen(dir) + 1);
		strlcpy(dir_, dir, strlen(dir) + 1);
		dir2 = dir_;
		do {
			str = strsep(&dir2, "/");
			nlog("str:%s dir2:%s", str, dir2);
			printf("\
 <a href='#'>%s</a> / ", str);
		} while (dir2 != NULL);
		if (dir_ != NULL)
			free(dir_);
	}
	if (page != NULL) {
		printf(" &rarr; %s", page);
	}
	printf("<hr/>\n");
}
