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
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <mtemplate.h>
#include <string.h>
#include <dirent.h>

#include "myhtml.h"
#include "util.h"

#include "breadcrumbs.h"

struct mobject *
breadcrumbs_make(char *dir)
{
	struct mobject *bcs = NULL;
	char           *str = NULL;
	char           *dir_;
	char           *dir2;
	char           *href_dir;
	int 		hdl;
	int 		run1 = 1;
	char           *a;

	if ((bcs = mdict_new()) == NULL)
		return NULL;

	a = make_url("index", NULL, NULL);
	mdict_insert_ss(bcs, "root", a);

	if ((dir != NULL) && (strlen(dir) > 0)) {
		hdl = strlen(dir) + 1 + 1;
		href_dir = malloc(strlen(dir) + 1 + 1);
		nlog("dir:%s", dir);
		href_dir[0] = '\0';
		dir_ = malloc(strlen(dir) + 1);
		strlcpy(dir_, dir, strlen(dir) + 1);
		dir2 = dir_;
		nlog("dir2:%s", dir2);

		do {
			str = strsep(&dir2, "/");
			if (run1)
				run1 = 0;
			else
				strlcat(href_dir, "/", hdl);
			strlcat(href_dir, str, hdl);
			nlog("href_dir:%s str:%s dir2:%s", href_dir, str, dir2);

			a = make_url("index", href_dir, NULL);
			mdict_insert_ss(bcs, str, a);
		} while (dir2 != NULL);

		free(dir_);
		free(href_dir);
	}
	return bcs;
}

struct mobject *
breadcrumbs_make_actions(char *dir, char *page, char *pagetype)
{
	char           *a;
	struct mobject *actions = NULL;

	if ((actions = mdict_new()) == NULL)
		return NULL;

	if ((page != NULL) && (pagetype != NULL)) {
		if (strcmp(pagetype, "view") == 0) {
			a = make_url("edit", dir, page);
			mdict_insert_ss(actions, "(edit)", a);
		} else if (strcmp(pagetype, "edit") == 0) {
			a = make_url("view", dir, page);
			mdict_insert_ss(actions, "(view)", a);
			a = make_url("delete", dir, page);
			mdict_insert_ss(actions, "(delete)", a);
		}
	} else {
		mdict_insert_ss(actions, "[new]", make_url("new", dir, NULL));
		mdict_insert_ss(actions, "[new-d]", make_url("newdir", dir, NULL));
		mdict_insert_ss(actions, "[del-d]", make_url("deldir", dir, NULL));
	}

	return actions;
}
