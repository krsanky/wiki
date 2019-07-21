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
#include <dirent.h>
#include <mtemplate.h>

#include "util.h"
#include "myhtml.h"
#include "params.h"
#include "wiki.h"

const int 	NUM_HTTP_PARAMS = 10;

int
main(void)
{
	char           *qs;
	PARAMS         *ps;
	char           *page;
	char           *dir;
	char           *pagetype;

	qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	if ((ps = params_create(NUM_HTTP_PARAMS, qs)) == NULL) {
		errpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	pagetype = ps->params[0].key;
	nlog("main.c main() QUERY_STRING:%s pagetype:%s", qs, pagetype);

	if (strlen(qs) < 1) {
		wikiindex(NULL);
	} else if (strcmp(pagetype, "index") == 0) {
		wikiindex(params_get(ps, "d"));
	} else if (strcmp(pagetype, "view") == 0) {
		page = params_get(ps, "p");
		if (page != NULL) {
			nlog("main view param:%s", page);
			wikiview(params_get(ps, "d"), page);
		} else
			errpage("param p (page) not found");
	} else if (strcmp(pagetype, "edit") == 0) {
		page = params_get(ps, "p");
		dir = params_get(ps, "d");
		wikiedit(dir, page);
	} else if (strcmp(pagetype, "editform") == 0) {
		wikieditform();
	} else if (strcmp(pagetype, "new") == 0) {
		wikinew(params_get(ps, "d"));
	} else if (strcmp(pagetype, "newform") == 0) {
		wikinewform();
	} else if (strcmp(pagetype, "delete") == 0) {
		page = params_get(ps, "p");
		dir = params_get(ps, "d");
		wikidelete(dir, page);
	} else if (strcmp(pagetype, "deldir") == 0) {
		msgpage("deldir");
	} else if (strcmp(pagetype, "newdir") == 0) {
		wikinewdir(params_get(ps, "d"));
	} else if (strcmp(pagetype, "newdirform") == 0) {
		wikinewdirform();
	} else if (strcmp(pagetype, "options") == 0) {
		wikioptions();
	}
	params_free(ps);
	return EXIT_SUCCESS;
}
