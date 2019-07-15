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

#include "breadcrumbs.h"

#include "myhtml.h"

#define EXTRA_JS "myhtml_extra_js"
#define EXTRA_CSS "myhtml_extra_css"

static char    *_altstyle = NULL;

/*
 * free this with mobject_free or mdict_free
 */
struct mobject *
myhtml_data_new()
{
	struct mobject *ns;

	ns = mdict_new();
	if (ns != NULL) {
		mdict_insert_sa(ns, EXTRA_JS);
		mdict_insert_sa(ns, EXTRA_CSS);
		/*
		 * example:struct mobject *tmp = mdict_item_s(ns, EXTRA_JS);
		 * marray_append_s(tmp, "/bad/js/include.js");
		 */
	}
	return ns;
}

void
myhtml_set_altstyle(char *s)
{
	free(_altstyle);
	_altstyle = s;
}

char           *
myhtml_get_altstyle()
{
	return _altstyle;
}

void
myhtml_test_altstyle()
{
	printf("<p>_altstyle:%s</p>\n", _altstyle);
}

void
myhtml_header_add_js(struct mobject * ns, char *js)
{
	struct mobject *tmp;
	tmp = mdict_item_s(ns, EXTRA_JS);
	marray_append_s(tmp, js);
}

void
myhtml_header_add_css(struct mobject * ns, char *css)
{
	struct mobject *tmp;
	tmp = mdict_item_s(ns, EXTRA_CSS);
	marray_append_s(tmp, css);
}

void
myhtml_header(struct mobject * ctx)
{
	char 		t       [] = "templates/header.m";
	struct mobject *data;
	if (ctx == NULL) {
		data = myhtml_data_new();
		tmpl_render(t, data);
		mobject_free(data);
		return;
	}
	tmpl_render(t, ctx);
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
	char 		t        [] = "templates/breadcrumbs.m";
	struct mobject *ctx = NULL;
	struct mobject *bcs = NULL;
	struct mobject *actions = NULL;

	if ((ctx = mdict_new()) == NULL) {
		nlog("mdict_new() error");
		goto end;
	}
	if (page != NULL)
		mdict_insert_ss(ctx, "page", page);
	else
		mdict_insert_ss(ctx, "page", "");

	bcs = breadcrumbs_make(dir);
	if (bcs == NULL) {
		nlog("breadcrumbs_make() error");
		goto end;
	}
	mdict_insert_s(ctx, "breadcrumbs", bcs);

	actions = breadcrumbs_make_actions(dir, page, pagetype);
	if (actions == NULL) {
		nlog("breadcrumbs_make_actions() error");
		goto end;
	}
	mdict_insert_s(ctx, "actions", actions);

	tmpl_render(t, ctx);
end:
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
myhtml_banner() 
{
	printf("<header><h2><a href='/wiki.cgi'>Oldcode Wiki</a></h2></header>\n");
}

void
myhtml_bannerA()
{
	printf("<a href='/'>wiki.oldcode.org</a>\n");
/*	printf("<a href='#'>[reload]</a>\n");*/
	printf("<hr/>\n");
}

