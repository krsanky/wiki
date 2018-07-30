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
	char           *href_dir;
	int 		hdl;

	printf("/");

	if (dir != NULL) {
		hdl = strlen(dir) + 1 + 1;
		href_dir = malloc(strlen(dir) + 1 + 1);
		nlog("dir:%s", dir);
		href_dir[0] = '\0';
		dir_ = malloc(strlen(dir) + 1);
		strlcpy(dir_, dir, strlen(dir) + 1);
		dir2 = dir_;
		do {
			str = strsep(&dir2, "/");
			strlcat(href_dir, "/", hdl);
			strlcat(href_dir, str, hdl);
			nlog("href_dir:%s str:%s dir2:%s", href_dir, str, dir2);

			printf("\
 <a href='/wiki.cgi?index&d=%s'>%s</a> / ", href_dir, str);

		} while (dir2 != NULL);
		free(dir_);
		free(href_dir);
	}
	if (page != NULL) {
		printf(" &rarr; %s", page);
	}
	printf("<hr/>\n");
}
