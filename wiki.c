/*
 * Copyright (c) 2019 Paul Wisehart paul@oldcode.org
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>
#include <dirent.h>
#include <mkdio.h>
#include <fcntl.h>
#include <mtemplate.h>

#include "myhtml.h"
#include "params.h"
#include "settings.h"
#include "util.h"
#include "forms.h"
#include "tmpl.h"

#include "wiki.h"

extern char   **environ;

void
errpage(char *fmt,...)
{
	char           *error;
	va_list 	ap;
	char           *errerr = "error in errpage :(";
	int 		ret;

	if ((error = malloc(256)) == NULL)
		error = errerr;

	va_start(ap, fmt);
	ret = vsnprintf(error, 256, fmt, ap);
	va_end(ap);

	http_headers();
	myhtml_header();
	printf("<p style='color:red;'>%s</p>\n", error);
	myhtml_footer();

	free(error);
}

void
msgpage(char *fmt,...)
{
	char           *msg;
	va_list 	ap;
	char           *errerr = "error in msgpage :(";
	int 		ret;

	if ((msg = malloc(256)) == NULL)
		msg = errerr;

	va_start(ap, fmt);
	ret = vsnprintf(msg, 256, fmt, ap);
	va_end(ap);

	http_headers();
	myhtml_header();
	printf("<p style='color:green;'>%s</p>\n", msg);
	myhtml_footer();
	free(msg);
}

void
showenv()
{
	char           *data = getenv("QUERY_STRING");

	printf("<pre>\n");
	if (data == NULL)
		printf("Error! Error in passing data from form to script.\n");
	else
		printf("QUERY_STRING[%s]\n", data);

	printf("---------------\n");

	for (char **env = environ; *env; ++env)
		printf("%s\n", *env);

	printf("</pre>\n");
}

char           *
fulldir(char *dir)
{
	char           *fulldir = NULL;
	int 		dirl;

	if (dir == NULL) {
		fulldir = strdup(WIKI_ROOT);
	} else {
		dirl = sizeof(WIKI_ROOT) + strlen(dir) + 1;
		fulldir = malloc(dirl);
		if (fulldir == NULL)
			return NULL;
		strlcpy(fulldir, WIKI_ROOT, dirl);
		strlcat(fulldir, "/", dirl);
		strlcat(fulldir, dir, dirl);
	}
	return fulldir;
}

/*
 * Doesn't mostly strings (char *) need the double pointer thing?
 * IOW "list" can be just a single pointer?
 */
int
make_mobject_dirlist(char *dir, struct mobject ** list)
{
	DIR            *d;
	char           *fd;
	struct dirent  *de;
	int 		ret = 0;
	struct mobject *pages, *dirs;
	char           *anchor;
	char           *tmpdir;

	fd = fulldir(dir);
	d = opendir(fd);
	if (d == NULL) {
		printf("could not open dir:%s", fd);
		ret = -1;
		goto end;
	}
	if ((*list = mdict_new()) == NULL) {
		printf("mdict_new error");
		ret = -1;
		goto end;
	}
	mdict_insert_sd(*list, "pages");
	mdict_insert_sd(*list, "dirs");
	pages = mdict_item_s(*list, "pages");
	dirs = mdict_item_s(*list, "dirs");
	while ((de = readdir(d)) != NULL) {
		if (de->d_name[0] != '.') {
			if (de->d_type == DT_DIR) {
				if (dir != NULL)
					ret = cat_strings(&tmpdir, 3, dir, "/", de->d_name);
				else
					ret = cat_strings(&tmpdir, 1, de->d_name);

				anchor = make_anchor("index", tmpdir, NULL, de->d_name);
				mdict_insert_ss(dirs, de->d_name, anchor);
				free(anchor);
				free(tmpdir);
			} else if (is_md(de)) {
				anchor = make_anchor("view", dir, de->d_name, de->d_name);
				mdict_insert_ss(pages, de->d_name, anchor);
				free(anchor);
			}
		}
	}

end:
	free(fd);
	if (d != NULL)
		closedir(d);
	return ret;
}

void
wikiindex(char *dir)
{
	struct mobject *ns = NULL;
	char 		t        [] = "templates/dirlist.m";

	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, NULL, NULL);

	if (make_mobject_dirlist(dir, &ns) == 0) {
		if (dir != NULL)
			mdict_insert_ss(ns, "dir", dir);
		else
			mdict_insert_ss(ns, "dir", "");
		tmpl_render(t, ns);
	}
	myhtml_footer();
	if (ns != NULL)
		mobject_free(ns);
}

void
wikiview(char *dir, char *page)
{
	int 		val;
	MMIOT          *mmiot;
	FILE           *mdfile;
	char           *fullpath;
	int 		fpl;

	nlog("wikiview(%s, %s)", dir, page);
	fpl = sizeof(WIKI_ROOT) + strlen(page) + 1;
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
	if (mdfile == NULL) {
		errpage("cannot open input file:");
		goto end;
	}
	mmiot = mkd_in(mdfile, 0);

	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, page, "view");
	val = markdown(mmiot, stdout, MKD_GITHUBTAGS);
	myhtml_footer();

end:
	if (mdfile != NULL)
		fclose(mdfile);
	free(fullpath);
}

void
wikiedit(char *dir, char *page)
{
	int 		fpl;
	char           *fullpath;
	FILE           *mdfile;
	char 		c;

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
	myhtml_header();
	myhtml_breadcrumbs(dir, page, "edit");
	myhtml_textarea_open();

	while ((c = fgetc(mdfile)) != EOF)
		printf("%c", c);

	if (mdfile != NULL)
		fclose(mdfile);

	myhtml_textarea_close(dir, page);
	myhtml_footer();
}

/*
 * This is being handled by wikieditform.php currently.
 * BUT, form is now urlencoded so we can go back to this.
 */
void
wikieditform()
{
	char           *RM;
	char           *CL_;
	char           *CT;
	int 		CL;
	char           *buf;
	int 		l = 0;
	char           *boundary;
	PARAMS         *ps;
	int 		NPARAMS = 4;

	RM = getenv("REQUEST_METHOD");
	CL_ = getenv("CONTENT_LENGTH");
	CT = getenv("CONTENT_TYPE");
	if (CL_ != NULL)
		CL = atoi(CL_);
	else
		CL = -1;

	nlog("editform() RM[%s] CT[%s] CL[%d]", RM, CT, CL);

	nlog("pre parse_b...");
	boundary = parse_boundary(CT);
	nlog("post parse_b...");

	ps = params_create(NPARAMS, NULL);

	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(NULL, NULL, "edit");


	buf = malloc(CL);
	/* try using CONTENT_LENGTH */
	if (buf != NULL) {
		l = fread(buf, 1, CL, stdin);
		/*
		params_parse_multipart_POST(buf, boundary, params, NPARAMS);
		*/
	}
	printf("<pre>\n");
	printf("boundary[%s]\n", boundary);
	printf("buf:\n%s\n", buf);
	printf("</pre>\n");

	printf("<hr/>\n");
	showenv();
	myhtml_footer();

	params_free(ps);
	free(boundary);
	free(buf);
	free(NULL);
}

void
wikinew(char *dir)
{
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, NULL, "new");
	myhtml_new(dir);
	myhtml_footer();
}
void
wikinewform()
{
	char           *RM;
	char           *CL_;
	char           *CT;
	int 		CL;
	char           *buf;
	int 		l;
	int 		ret;
	char           *decode;

	PARAMS         *ps;
	int 		NPARAMS = 5;
	char           *page;
	char           *dir;

	RM = getenv("REQUEST_METHOD");
	CL_ = getenv("CONTENT_LENGTH");
	CT = getenv("CONTENT_TYPE");
	if (CL_ != NULL)
		CL = atoi(CL_);
	else
		CL = -1;

	nlog("wikinewform() RM[%s] CT[%s] CL[%d]", RM, CT, CL);

	buf = malloc(CL);
	if (buf != NULL) {
		l = fread(buf, 1, CL, stdin);
		nlog("buf:%s", buf);
		ps = params_create(NPARAMS, buf);
		free(buf);

		page = params_get(ps, "page");
		dir = params_get(ps, "dir");
		if (dir == NULL)
			dir = "";
		nlog("make new file dir:%s page:%s", dir, page);
		/*
		 * dir is http/html encode ? params_urldecode(char *s, char
		 * *dec)
		 */
		decode = malloc(strlen(dir) + 1);
		if (decode == NULL) {
			errpage("malloc error");
			return;
		}
		ret = params_urldecode(dir, decode);
		nlog("params_urldecode: ret:%d decode:%s", ret, decode);
		nlog("dir:%s  strlen(dir):%d sizeof(dir):%d", dir, strlen(dir), sizeof(dir));
		strlcpy(dir, decode, sizeof(dir));
		free(decode);

		char           *fullpath;
		FILE           *newfile;
		int 		fpl;

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
		nlog("wikinewform:: fullpath:%s", fullpath);

		newfile = fopen(fullpath, "a");
		free(fullpath);
		if (newfile == NULL) {
			errpage("cannot create file:");
			return;
		}
		if (newfile != NULL)
			fclose(newfile);


		/* msgpage("new file created"); */
		self_redirect("index", dir, NULL);
		params_free(ps);
		return;
	}
	errpage("error creating new file");
}

void
wikidelete(char *dir, char *page)
{
	char           *delpath;
	int 		dpl = strlen(WIKI_ROOT) + 1 + 10;
	/* eol and to not count slashes */

	if (dir != NULL)
		dpl += strlen(dir);
	if (page != NULL)
		dpl += strlen(page);
	nlog("WIKIDELETE dir:%s page:%s l:%d", dir, page, dpl);
	delpath = malloc(dpl);
	if (delpath != NULL) {
		strlcpy(delpath, WIKI_ROOT, dpl);
		if (dir != NULL) {
			strlcat(delpath, "/", dpl);
			strlcat(delpath, dir, dpl);
		}
		if (page != NULL) {
			strlcat(delpath, "/", dpl);
			strlcat(delpath, page, dpl);
		}
		nlog("delpath:%s", delpath);
		unlink(delpath);
		free(delpath);
		/* msgpage("file/dir deleted?"); */

		/* redir to dir or WIKI_ROOT */
		self_redirect("index", dir, NULL);
		return;
	}
	errpage("error deleting");
}

/*
typedef struct wikipage {
	char 		url      [256];
	char 		name     [128];
} 		Page;
*/
int
GetPages(FILE * dir, Page ** ps)
{
	/*
		int 		ratesBufSize = 9;
		*rates = malloc(sizeof(Rate) * ratesBufSize);
	*/
	/* just read the file(no need to open) */

	return 0;
	//line_count / 2;
}

int
AlphaPages(Page ** ps)
{
	/* iterate thru and keep moving A to front */
	return 0;
}
