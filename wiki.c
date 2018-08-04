#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <mkdio.h>

#include "wiki.h"
#include "myhtml.h"
#include "yuarel.h"
#include "settings.h"
#include "util.h"

extern char   **environ;


void
http_headers(void)
{
	printf("Content-type: text/html\n\n");
}

void
query_params_test(struct yuarel_param * params, int sz)
{
	char           *qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errpage("error with QUERY_STRING");
		return;
	}
	if (sz < 0) {
		errpage("error with yuarel_parse_query()");
		return;
	}
	http_headers();

	myhtml_header();
	/* myhtml_topnav(NULL, NULL); */
	printf("<dl>\n");
	while (sz-- > 0) {
		printf("<dt>%s</dt><dd>%s</dd>\n", params[sz].key, params[sz].val);
	}
	printf("</dl>\n");

	myhtml_footer();
}

void
mainpage(void)
{
	http_headers();

	myhtml_header();
	/* myhtml_topnav(NULL, NULL); */
	printf("\
<p>wiki wiki wiki</p>\n\
<ul>\n\
<li><a href='/wiki.cgi?index'>index</a></li>\
</ul>\n");

	showenv();

	myhtml_footer();
}

void
errpage(char *error)
{
	http_headers();

	myhtml_header();
	/* myhtml_topnav(NULL, NULL); */
	printf("\
<p style='color:red;'>%s</p>\n", error);
	myhtml_footer();
}

void
msgpage(char *msg)
{
	http_headers();

	myhtml_header();
	/* myhtml_topnav(NULL, NULL); */
	printf("\
<p style='color:green;'>%s</p>\n", msg);
	myhtml_footer();
}

void
showenv()
{
	printf("<pre>\n");
	char           *data = getenv("QUERY_STRING");
	if (data == NULL)
		printf("Error! Error in passing data from form to script.\n");
	else
		printf("QUERY_STRING[%s]\n", data);

	puts("---------------");

	for (char **env = environ; *env; ++env)
		printf("%s\n", *env);

	printf("</pre>\n");
}

int
is_md(struct dirent * de)
{
	char           *ext;
	ext = strrchr(de->d_name, '.');
	if (ext != NULL) {
		ext++;
		if (strcasecmp(ext, "md") == 0)
			if (de->d_type == DT_REG)
				return 1;
	}
	return 0;
}

void
wikiindex(char *dir_)
{
	struct dirent  *de;
	DIR            *dir;
	int 		dirl = 0;
	char           *fulldir;

	if (dir_ == NULL) {
		fulldir = WIKI_ROOT;
	} else {
		dirl = sizeof(WIKI_ROOT) + strlen(dir_) + 1;
		fulldir = malloc(dirl);
		strlcpy(fulldir, WIKI_ROOT, dirl);
		strlcat(fulldir, "/", dirl);
		strlcat(fulldir, dir_, dirl);
	}
	nlog("dir_:%s fulldir:%s", dir_, fulldir);

	dir = opendir(fulldir);
	if (dir == NULL) {
		errpage("could not open dir:");
	}
	if (dirl > 0)
		free(fulldir);

	http_headers();
	myhtml_header();
	/* myhtml_topnav(dir_, NULL); */
	myhtml_breadcrumbs(dir_, NULL, NULL);
	printf("<ul>\n");
	while ((de = readdir(dir)) != NULL) {
		if (is_md(de)) {
			if (dir_ == NULL) {
				printf("\
<li>\
<a href='/wiki.cgi?view&p=%s'>\
%s\
</a></li>\n", de->d_name, de->d_name);
			} else {
				printf("\
<li>\
<a href='/wiki.cgi?view&d=%s&p=%s'>\
%s\
</a></li>\n", dir_, de->d_name, de->d_name);

			}

		} else if ((de->d_type == DT_DIR) && (de->d_name[0] != '.')) {
			if (dir_ == NULL) {
				printf("\
<li>\
<a href='/wiki.cgi?index&d=%s'>\
dir:%s\
</a></li>\n", de->d_name, de->d_name);
			} else {
				printf("\
<li>\
<a href='/wiki.cgi?index&d=%s/%s'>\
dir:%s\
</a></li>\n", dir_, de->d_name, de->d_name);
			}
		}
	}
	printf("</ul>\n");
	myhtml_footer();

	closedir(dir);
}


void
wikiview(char *dir, char *filename)
{
	int 		val;
	MMIOT          *mmiot;
	FILE           *mdfile;
	char           *fullpath;
	int 		fpl;

	fpl = sizeof(WIKI_ROOT) + 1 + strlen(filename);
	if (dir != NULL)
		fpl = fpl + strlen(dir) + 1;
	fullpath = malloc(fpl);
	strlcpy(fullpath, WIKI_ROOT, fpl);
	strlcat(fullpath, "/", fpl);
	if (dir != NULL) {
		strlcat(fullpath, dir, fpl);
		strlcat(fullpath, "/", fpl);
	}
	strlcat(fullpath, filename, fpl);
	nlog("wikiview fullpath:%s", fullpath);

	mdfile = fopen(fullpath, "r");
	free(fullpath);
	if (mdfile == NULL) {
		errpage("cannot open input file:");
	}
	mmiot = mkd_in(mdfile, 0);

	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, filename, "view");
	val = markdown(mmiot, stdout, MKD_GITHUBTAGS);
	myhtml_footer();

	if (mdfile != NULL)
		fclose(mdfile);
}

char           *
get_param(char *pname, struct yuarel_param * params, int sz)
{
	nlog("get_param( %s )", pname);

	for (int i = 0; i < sz; i++)
		if (params[i].key != NULL)
			if (strcmp(pname, params[i].key) == 0)
				return params[i].val;
	return NULL;
}

void
wikiedit(char *dir, char *page)
{
	int 		fpl;
	char           *fullpath;
	FILE           *mdfile;
	char 		ch;

	fpl = sizeof(WIKI_ROOT) + 1 + strlen(page);
	if (dir != NULL)
		fpl = fpl + strlen(dir) + 1;
	fullpath = malloc(fpl);
	strlcpy(fullpath, WIKI_ROOT, fpl);
	strlcat(fullpath, "/", fpl);
	if (dir != NULL) {
		strlcat(fullpath, dir, fpl);
		strlcat(fullpath, "/", fpl);
	}
	strlcat(fullpath, page, fpl);
	nlog("wikiview fullpath:%s", fullpath);

	mdfile = fopen(fullpath, "r");
	free(fullpath);
	if (mdfile == NULL) {
		errpage("cannot open input file:");
		return;
	}
	http_headers();
	/* form_http_headers(); */
	myhtml_header();
	myhtml_breadcrumbs(dir, page, "edit");
	myhtml_textarea_open();

	ch = fgetc(mdfile);
	while (ch != EOF) {
		printf("%c", ch);
		ch = fgetc(mdfile);
	}

	fclose(mdfile);

	myhtml_textarea_close(dir, page);
	myhtml_footer();
}

inline int 
ishex(int x)
{
	return (x >= '0' && x <= '9') ||
	(x >= 'a' && x <= 'f') ||
	(x >= 'A' && x <= 'F');
}

int 
urldecode(const char *s, char *dec)
{
	char           *o;
	const char     *end = s + strlen(s);
	int 		c;

	for (o = dec; s <= end; o++) {
		c = *s++;
		if (c == '+')
			c = ' ';
		else if (c == '%' && (!ishex(*s++) ||
				      !ishex(*s++) ||
				      !sscanf(s - 2, "%2x", &c)))
			return -1;

		if (dec)
			*o = c;
	}

	return o - dec;
}

void
wikieditform()
{
	/*
	 * This is HTTP so must be sent before any content. printf "Location:
	 * http://newdomain.com/newfile.pl\n\n"; printf "Location:
	 * /newfile.pl\n\n"; CONTENT_LENGTH=362
	 * CONTENT_TYPE=application/x-www-form-urlencoded REQUEST_METHOD=POST
	 * 
	 * char buffer[10]; read(STDIN_FILENO, buffer, 10);
	 */
	char           *RM;
	char           *CL_;
	int 		CL;
	char           *buf;
	char           *decode;
	int 		ret;

	RM = getenv("REQUEST_METHOD");
	CL_ = getenv("CONTENT_LENGTH");
	if (CL_ != NULL)
		CL = atoi(CL_);
	else
		CL = -1;
	nlog("editform()...RM:%s CL:%d", RM, CL);

	if (CL > 0) {
		buf = malloc(CL + 1);
		decode = malloc(CL + 1);
		fread(buf, CL, 1, stdin);
		nlog("buf:%s", buf);
		ret = urldecode(buf, decode);
		if (ret > 0)
			nlog("decode:%s", decode);
		else
			nlog("decode: error");
		free(buf);
		free(decode);
	} else {
		nlog("editform error getting CONTENT_LENGTH value");
	}


	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(NULL, NULL, NULL);
	showenv();
	myhtml_footer();
}

void
wikinew(char *dir, char *page)
{
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, page, "new");
	myhtml_footer();
}
