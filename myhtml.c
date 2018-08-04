#include <stdlib.h>
#include <stdio.h>
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

/* not used? */
void
myhtml_topnav(char *dir, char *page)
{
	printf("<hr/>\n");
	printf("<a href=\"/\">home</a> ");
	printf("<a href='/wiki.cgi?index'>index</a>\n");
	if (page != NULL) {
		printf("\
<a href='/wiki.cgi?edit&d=%s&p=%s'>edit</a> ", dir, page);
	} else {
		if (dir == NULL) {
			printf("\
<a href='/wiki.cgi?new'>new</a> ");
		} else {
			printf("\
<a href='/wiki.cgi?new&d=%s'>new</a> ", dir);
		}
	}
	printf("<hr/>\n");
}

void
myhtml_breadcrumbs(char *dir, char *page, char *pagetype)
{
	char           *str = NULL;
	char           *dir_;
	char           *dir2;
	char           *href_dir;
	int 		hdl;
	int 		run1 = 1;
	char           *a;

	a = make_anchor("index", NULL, NULL, "root");
	printf("/ %s / ", a);
	free(a);

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
			if (run1)
				run1 = 0;
			else
				strlcat(href_dir, "/", hdl);
			strlcat(href_dir, str, hdl);
			nlog("href_dir:%s str:%s dir2:%s", href_dir, str, dir2);

			a = make_anchor("index", href_dir, NULL, str);
			printf(" %s / ", a);
			free(a);

		} while (dir2 != NULL);

		free(dir_);
		free(href_dir);

	}
	if ((page != NULL) && (pagetype != NULL)) {
		printf("%s ", page);
		if (strcmp(pagetype, "view") == 0) {
			a = make_anchor("edit", dir, page, "(edit)");
			printf("%s\n", a);
			free(a);
		} else if (strcmp(pagetype, "edit") == 0) {
			a = make_anchor("view", dir, page, "(view)");
			printf("%s\n", a);
			free(a);
		}
	} else {
		printf("%s  ", make_anchor("new", dir, NULL, "[new]"));
	}
	printf("<hr/>\n");
}


/*
 * <a href='/wiki.cgi?edit&d=%s&p=%s'>(edit)</a> ", dir, page); Return value
 * must be free'd. The longest possible formaty string is used for the fmt
 * size.
 */
char           *
make_anchor(char *pagetype, char *dir, char *page, char *display)
{
	int 		max_l;
	char           *a;

	max_l = strlen("<a href='/wiki.cgi?edit&d=%s&p=%s'>(edit)</a>");
	if (pagetype != NULL)
		max_l += strlen(pagetype);
	if (dir != NULL)
		max_l += strlen(dir);
	if (page != NULL)
		max_l += strlen(page);
	if (display != NULL)
		max_l += strlen(display);
	max_l += 1;
	a = malloc(max_l);
	if (a == NULL)
		return NULL;

	strlcpy(a, "<a href='/wiki.cgi?", max_l);
	strlcat(a, pagetype, max_l);
	strlcat(a, "&", max_l);

	if (dir != NULL) {
		strlcat(a, "d=", max_l);
		strlcat(a, dir, max_l);
		strlcat(a, "&", max_l);
	}
	if (page != NULL) {
		strlcat(a, "p=", max_l);
		strlcat(a, page, max_l);
	}
	strlcat(a, "'>", max_l);

	if (display != NULL)
		strlcat(a, display, max_l);
	else
		strlcat(a, pagetype, max_l);

	strlcat(a, "</a>", max_l);

	return a;
}

void
myhtml_textarea_open()
{
	printf("\
<form action='/wiki.cgi?editform' method='post' \
 enctype='application/x-www-form-urlencoded'>\n\
<textarea name=\"wikiformtext\" rows='26' cols='80'>");
}

void
myhtml_textarea_close(char *dir, char *page)
{
	printf("\
</textarea>\n\
<br/>\n\
<button type='submit'>submit</button>\n\
<input type='hidden' name='dir' value='%s'/>\
<input type='hidden' name='page' value='%s'/>\
</form>\n", dir, page);
}
