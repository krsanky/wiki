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
#include <assert.h>

#include "myhtml.h"
#include "params.h"
#include "settings.h"
#include "util.h"
#include "forms.h"
#include "tmpl.h"
#include "sort_mdict.h"

#include "wiki_file_io.h"

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
	myhtml_header(NULL);
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
	myhtml_header(NULL);
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

void
populate_dirs(struct mobject * dirs, char *basedir, char **darr, int darrl)
{
	int 		i;
	char           *tmpd, *anchor, *s1;

	if (mobject_type(dirs) != TYPE_MDICT) {
		nlog("error dirs is not an mdict");
		return;
	}
	for (i = 0; i < darrl; i++) {
		if (basedir != NULL)
			cat_strings(&tmpd, 3, basedir, "/", darr[i]);
		else
			cat_strings(&tmpd, 1, darr[i]);

		anchor = make_anchor("index", tmpd, NULL, darr[i]);
		s1 = strdup(darr[i]);
		mdict_insert_ss(dirs, s1, anchor);
		free(anchor);
		free(tmpd);
	}
}

void
populate_pages(struct mobject * pages, char *basedir, char **parr, int parrl)
{
	int 		i;
	char           *tmpd, *anchor, *s1;

	if (mobject_type(pages) != TYPE_MDICT) {
		nlog("error pages is not an mdict");
		return;
	}
	for (i = 0; i < parrl; i++) {
		if (basedir != NULL)
			cat_strings(&tmpd, 3, basedir, "/", parr[i]);
		else
			cat_strings(&tmpd, 1, parr[i]);


		anchor = make_anchor("view", basedir, parr[i], parr[i]);


		s1 = strdup(parr[i]);
		mdict_insert_ss(pages, s1, anchor);
		free(anchor);
		free(tmpd);
	}
}

void
wikiindex(char *dir)
{
	struct mobject *ns = NULL;
	struct mobject *pages, *dirs;
	char 		t        [] = "templates/dirlist.m";
	char           *fd;

	fd = fulldir(dir);

	assert((ns = mdict_new()) != NULL);
	if (dir != NULL)
		mdict_insert_ss(ns, "dir", dir);
	else
		mdict_insert_ss(ns, "dir", "");

	mdict_insert_sd(ns, "pages");
	mdict_insert_sd(ns, "dirs");
	pages = mdict_item_s(ns, "pages");
	dirs = mdict_item_s(ns, "dirs");

	int 		psl      , dsl;
	char          **ps, **ds;
	ds = make_sorted_dir_arr(fd, &dsl);
	ps = make_sorted_page_arr(fd, &psl);
	populate_dirs(dirs, dir, ds, dsl);
	populate_pages(pages, dir, ps, psl);

	http_headers();
	myhtml_header(NULL);
	myhtml_banner();
	myhtml_breadcrumbs(dir, NULL, NULL);

	tmpl_render(t, ns);

	myhtml_footer();
	mobject_free(ns);
	free(fd);
	free_sorted_arr(ps, psl);
	free_sorted_arr(ds, dsl);
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
		if (strlen(dir) != 0) {
			strlcat(fullpath, dir, fpl);
			strlcat(fullpath, "/", fpl);
		}
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
	myhtml_header(NULL);
	myhtml_banner();
	myhtml_breadcrumbs(dir, page, "view");
	val = markdown(mmiot, stdout, MKD_GITHUBTAGS | MKD_FENCEDCODE);
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

	struct mobject *data;
	assert((data = myhtml_data_new()) != NULL);
	myhtml_header_add_css(data, "/static/codemirror-5.46.0/lib/codemirror.css");
	myhtml_header_add_css(data, "/static/codemirror-5.46.0/addon/dialog/dialog.css");
	myhtml_header_add_css(data, "/static/codemirror-5.46.0/theme/midnight.css");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/lib/codemirror.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/addon/dialog/dialog.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/addon/search/searchcursor.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/addon/edit/matchbrackets.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/keymap/vim.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/keymap/emacs.js");
	myhtml_header(data);
	myhtml_banner();

	myhtml_breadcrumbs(dir, page, "edit");

	myhtml_textarea_open();
	while ((c = fgetc(mdfile)) != EOF)
		printf("%c", c);
	if (mdfile != NULL)
		fclose(mdfile);
	myhtml_textarea_close(dir, page);

	/*
	 * printf("<div style='font-size: 13px; width: 300px; height:
	 * 30px;'>Key buffer: <span id='command-display'></span></div>\n");
	 */

	printf("<script src='/static/edit.js'></script>\n");
	myhtml_footer();
}

void
wikieditform()
{
	char           *RM;
	char           *CL_;
	char           *CT;
	int 		CL;
	char           *buf;
	int 		l;
	char           *txt;
	PARAMS         *ps;
	int 		NPARAMS = 5;
	char           *decode, *tmpstr;
	int 		ret;

	char           *fullpath;
	char           *page;
	char           *dir;
	FILE           *editfile;
	int 		fpl;

	RM = getenv("REQUEST_METHOD");
	CL_ = getenv("CONTENT_LENGTH");
	CT = getenv("CONTENT_TYPE");
	if (CL_ != NULL)
		CL = atoi(CL_);
	else
		CL = -1;

	nlog("editform() RM[%s] CT[%s] CL[%d]", RM, CT, CL);




	buf = malloc(CL);
	if (buf != NULL) {
		l = fread(buf, 1, CL, stdin);
		nlog("buf:%s", buf);
		ps = params_create(NPARAMS, buf);
		free(buf);
		txt = params_get(ps, "wikiformtext");
		decode = malloc(strlen(txt) + 1);

		if (decode == NULL) {
			errpage("malloc error");
			return;
		}
		ret = params_urldecode(txt, decode);
		nlog("txt decoded:%s", decode);

		page = params_get(ps, "page");
		dir = params_get(ps, "dir");

		if (dir != NULL) {
			tmpstr = malloc(strlen(dir) + 1);
			if (tmpstr == NULL) {
				errpage("malloc error");
				return;
			}
			ret = params_urldecode(dir, tmpstr);
			nlog("update file dir:%s page:%s tmpstr:%s", dir, page, tmpstr);
			dir = tmpstr;
		}
		nlog("update file dir*:%s page:%s", dir, page);

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
		nlog("wikieditform:: fullpath:%s", fullpath);

		/* -----wiki_writefile(fullpath_str) */
		editfile = fopen(fullpath, "w");
		free(fullpath);
		if (editfile == NULL) {
			errpage("cannot edit file (try again in code?):%s", fullpath);
			return;
		}
		fputs(decode, editfile);
		if (editfile != NULL)
			fclose(editfile);
		free(decode);

		self_redirect("view", dir, page);
		params_free(ps);
		free(dir);
		return;
	}
	http_headers();
	myhtml_header(NULL);
	myhtml_banner();
	myhtml_breadcrumbs(NULL, NULL, "edit");

	printf("<p>editform() RM[%s] CT[%s] CL[%d]</p>\n", RM, CT, CL);

	myhtml_footer();
}

void
wikinew(char *dir)
{
	char 		t        [] = "templates/new.m";
	http_headers();
	myhtml_header(NULL);
	myhtml_banner();
	myhtml_breadcrumbs(dir, NULL, "new");


	/* myhtml_new(dir); */
	struct mobject *namespace = NULL;

	if ((namespace = mdict_new()) == NULL) {
		nlog("mdict_new error dir:%s", dir);
		return;
	} else
		nlog("mdict_new OK dir:%s", dir);

	if (dir == NULL)
		mdict_insert_ss(namespace, "dir", "");
	else
		mdict_insert_ss(namespace, "dir", dir);

	tmpl_render(t, namespace);


	myhtml_footer();
	mobject_free(namespace);
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
		nlog("make new file dir:%s page:%s", dir, page);

		if (dir != NULL) {
			decode = malloc(strlen(dir) + 1);
			if (decode == NULL) {
				errpage("malloc error");
				return;
			}
			ret = params_urldecode(dir, decode);
			nlog("params_urldecode: ret:%d decode:%s", ret, decode);
			nlog("dir:%s  strlen(dir):%d sizeof(dir):%d", dir, strlen(dir), sizeof(dir));
			strlcpy(dir, decode, strlen(dir) + 1);
			nlog("after strlcpy- dir:%s  strlen(dir):%d sizeof(dir):%d", dir, strlen(dir), sizeof(dir));
			free(decode);
		}
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
		free(dir);	/* ??? */
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

void
wikioptions()
{
	char 		t        [] = "templates/options.m";
	struct mobject *data;
	PARAMS         *ps = NULL;

	assert((data = mdict_new()) != NULL);


/*
	char		*qs;
	if (strcasecmp(getenv("REQUEST_METHOD"), "POST") == 0) {
		printf("Set-Cookie:asdqwe = Qwert;\r\n");
		qs = getenv("QUERY_STRING");
		CL_ = getenv("CONTENT_LENGTH");
		buf = malloc(CL);
		assert(buf != NULL);

		l = fread(buf, 1, CL, stdin);
		nlog("buf:%s", buf);
		ps = params_create(NPARAMS, buf);
		free(buf);
		txt = params_get(ps, "wikiformtext");
	
		if (qs == NULL) {
			errpage("error with QUERY_STRING");
		}
		if ((ps = params_create(num_params, qs)) == NULL) {
			errpage("error with QUERY_STRING");
		}
		var2 = params_get(ps, "var2");
		nlog("var2:%s", var2);
	}	
*/


	http_headers();
	myhtml_header(NULL);

	showenv();

	tmpl_render(t, data);
	myhtml_footer();

	mobject_free(data);
	params_free(ps);
}



