/*
 * Copyright (c) 2018, 2019 Paul Wisehart <paul@oldcode.org>
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mtemplate.h>
#include <dirent.h>

#include "util.h"
#include "tmpl.h"

#include "myhtml.h"

void
myhtml_header()
{
	char 		fn       [] = "templates/header.m";
	tmpl_render(fn, NULL);
}

void
myhtml_footer()
{
	char 		fn       [] = "templates/footer.m";
	tmpl_render(fn, NULL);
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
			a = make_anchor("delete", dir, page, "(delete)");
			printf("%s\n", a);
			free(a);
		}
	} else {
		printf("%s  ", make_anchor("new", dir, NULL, "[new]"));
		printf("%s  ", make_anchor("delete", dir, NULL, "[delete]"));
	}
	printf("<hr/>\n");
}
void
myhtml_breadcrumbs2(char *dir, char *page, char *pagetype)
{
	char 		fn       [] = "templates/breadcrumbs.m";
	char 		lightgreen123[] = "#3c9";
	char           *a;
	struct mobject *ctx = NULL;

	if ((ctx = mdict_new()) == NULL) {
		nlog("mdict_new() error");
		tmpl_render(fn, NULL);
		return;
	}

	a = make_anchor("index", NULL, NULL, "root");
	nlog("a url:%s", a);
	mdict_insert_ss(ctx, "var1", "var1 example ...");




	char           *str = NULL;
	char           *dir_;
	char           *dir2;
	char           *href_dir;
	int 		hdl;
	int 		run1 = 1;
	if (dir != NULL) {
		hdl = strlen(dir) + 1 + 1;
		href_dir = malloc(strlen(dir) + 1 + 1);
		nlog("dir:%s", dir);
		href_dir[0] = '\0';
		dir_ = malloc(strlen(dir) + 1);
		strlcpy(dir_, dir, strlen(dir) + 1);
		dir2 = dir_;

		do {
			nlog("142 here"); 
			str = strsep(&dir2, "/");
			if (run1)
				run1 = 0;
			else
				strlcat(href_dir, "/", hdl);
			strlcat(href_dir, str, hdl);
			nlog("href_dir:%s str:%s dir2:%s", href_dir, str, dir2);
/*
			a = make_anchor("index", href_dir, NULL, str);
			nlog("151 %s / ", a);
			free(a);
			*/

		} while (dir2 != NULL);

		free(dir_);
		free(href_dir);
	}
	/*
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
			a = make_anchor("delete", dir, page, "(delete)");
			printf("%s\n", a);
			free(a);
		}
	}
	*/
	/* else {
		printf("%s  ", make_anchor("new", dir, NULL, "[new]"));
		printf("%s  ", make_anchor("delete", dir, NULL, "[delete]"));
	}*/


	tmpl_render(fn, ctx);
	free(a);
	mobject_free(ctx);
}


/*
 * <a href='/wiki.cgi?edit&d=%s&p=%s'>(edit)</a> ", dir, page); Return value
 * must be free'd. The longest possible format string is used for the fmt
 * size.
 */
char           *
make_anchor(char *pagetype, char *dir, char *page, char *display)
{
	int 		max_l;
	char           *a = NULL;

	max_l = strlen("<a href='/wiki.cgi?edit&amp;d=%s&amp;p=%s'>(edit)</a>");
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
	strlcat(a, "&amp;", max_l);

	if (dir != NULL) {
		strlcat(a, "d=", max_l);
		strlcat(a, dir, max_l);
		strlcat(a, "&amp;", max_l);
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
/*
 * must be free'd. The longest possible format string is used for the fmt
 */
char           *
make_url(char *pagetype, char *dir, char *page)
{
	int 		max_l;
	char           *a;

	max_l = strlen("/wiki.cgi?edit&d=%s&p=%s");
	if (pagetype != NULL)
		max_l += strlen(pagetype);
	if (dir != NULL)
		max_l += strlen(dir);
	if (page != NULL)
		max_l += strlen(page);
	max_l += 1;
	a = malloc(max_l);
	if (a == NULL)
		return NULL;

	strlcpy(a, "/wiki.cgi?", max_l);
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
	strlcat(a, "", max_l);

	return a;
}

void
myhtml_textarea_open()
{
	char 		fn       [] = "templates/textarea_open.m";
	tmpl_render(fn, NULL);
}

void
myhtml_textarea_close(char *dir, char *page)
{
	char 		fn       [] = "templates/textarea_close.m";
	struct mobject *namespace = NULL;

	if ((namespace = mdict_new()) == NULL) {
		nlog("mdict_new error dir:%s", dir);
		return;
	} else
		nlog("mdict_new OK dir:%s", dir);

	mdict_insert_ss(namespace, "page", page);
	if (dir == NULL)
		mdict_insert_ss(namespace, "dir", "");
	else
		mdict_insert_ss(namespace, "dir", dir);

	tmpl_render(fn, namespace);
	mobject_free(namespace);
}

void
myhtml_new(char *dir)
{
	char 		fn       [] = "templates/new.m";
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

	tmpl_render(fn, namespace);
	mobject_free(namespace);
}
