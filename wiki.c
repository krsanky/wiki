#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <mkdio.h>

#include "wiki.h"
#include "myhtml.h"
#include "params.h"
#include "settings.h"
#include "util.h"

extern char   **environ;


void
http_headers(void)
{
	printf("Content-type: text/html\n\n");
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

/**
 * This answers the POST from wikiedit.
 * This is the first form handling code.
 */
void
wikieditform()
{
	char           *RM;
	char           *CL_;
	int 		CL;
	char           *buf;
	int 		ret;
	int 		p;
	char           *wikiformtext;
	char           *rawwikiformtext;
	char           *redir;
	char           *dir;
	char           *page;

	RM = getenv("REQUEST_METHOD");
	CL_ = getenv("CONTENT_LENGTH");
	if (CL_ != NULL)
		CL = atoi(CL_);
	else
		CL = -1;

	nlog("editform()...RM:%s CL:%d", RM, CL);

	if (CL > 0) {
		buf = malloc(CL + 1);
		fread(buf, CL, 1, stdin);
		nlog("buf:%s", buf);
/*
		params = malloc(sizeof(*params) + NUM_HTTP_PARAMS);
		p = yuarel_parse_query(buf, '&', params, NUM_HTTP_PARAMS);
		if (p < 0) {
			nlog("error with yuarel_parse_query()");
		} else {
			nlog("param-0 k:%s v:%s", params[0].key, params[0].val);
		}
		rawwikiformtext = get_param("wikiformtext", params, NUM_HTTP_PARAMS);

		nlog("rawwikiformtext:%s", rawwikiformtext);
		wikiformtext = malloc(strlen(rawwikiformtext) + 1);
		ret = urldecode(rawwikiformtext, wikiformtext);
		nlog("wikiformtext:%s", wikiformtext);
		if (ret > 0) {
			nlog("wikiformtext:%s", wikiformtext);
		}

		dir = get_param("dir", params, NUM_HTTP_PARAMS);
		if (dir == NULL)
			nlog("dir==NULL");
		else
			nlog("dir!=NULL");
		page = get_param("page", params, NUM_HTTP_PARAMS);

		redir = make_url("edit", dir, page);
		nlog("dir:%s page:%s redir:%s", dir, page, redir);
		redirect(redir);
		free(redir);

		free(params);
*/
		free(buf);
	} else {
		nlog("editform error getting CONTENT_LENGTH value");
	}

}

void
wikinew(char *dir, char *page)
{
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, page, "new");
	myhtml_footer();
}
