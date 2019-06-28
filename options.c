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
#include <assert.h>

#include "util.h"
#include "tmpl.h"
#include "myhtml.h"
#include "params.h"
#include "wiki.h"
#include "forms.h"

void
set_cookie(char *n, char *v)
{
	printf("Set-Cookie:%s = %s;\r\n", n, v);
}

void
setup_data(struct mobject * data)
{
	mdict_insert_ss(data, "editor", UNDEFINED);
	mdict_insert_ss(data, "bogus_var1", UNDEFINED);
	mdict_insert_ss(data, "cookie", UNDEFINED);
}

void
add_cookie(char *name, char *val)
{
	if ((name == NULL) || (val == NULL))
		return;
	set_cookie(name, val);
}

int
main()
{
	char 		t        [] = "templates/options.m";
	struct mobject *data;
	PARAMS         *ps = NULL;
	PARAMS         *cps = NULL;
	char           *qs, *CL_, *buf;
	char           *cookie;
	char           *editor, *bogus_var1;
	int 		CL;
	int 		bufl;
	int		ret;
	int		i;

	assert((data = mdict_new()) != NULL);
	setup_data(data);

	/*
	 * Read cookies
	 * set_cookie("asdasd", "qweqwe");
	 * set_cookie("123_-123", "sdf wert  thter");
         * set_cookie("kkk-ppp", "asd 123 5345");
	 */
	if ((cookie = getenv("HTTP_COOKIE")) != NULL) {
		mdict_replace_ss(data, "cookie", cookie);
		assert((cps = params_new(5)) != NULL);
		ret = params_parse_http_cookie(cookie, cps);
		nlog("ret:%d", ret);
	}
	if (cps != NULL) {
		nlog("cps != NULL");
		for (i=0; i<cps->len; i++) {
			nlog("key:%s", cps->params[i].key);
		}
	}

	if (strcasecmp(getenv("REQUEST_METHOD"), "POST") == 0) {
		qs = getenv("QUERY_STRING");
		assert(qs != NULL);
		CL_ = getenv("CONTENT_LENGTH");
		CL = (CL_ != NULL) ? atoi(CL_) : -1;


		buf = malloc(CL);
		assert(buf != NULL);

		bufl = fread(buf, 1, CL, stdin);
		nlog("buf:%s", buf);
		assert((ps = params_create(5, buf)) != NULL);
		free(buf);

		add_cookie(params_get(ps, "cookie_name"), params_get(ps, "cookie_value"));

		editor = params_get(ps, "editor");
		bogus_var1 = params_get(ps, "bogus_var1");
		nlog("editor:%s", editor);
		mdict_replace_ss(data, "editor", editor);
		mdict_replace_ss(data, "bogus_var1", bogus_var1);
		set_cookie("bogus_var1", bogus_var1);
	}
	http_headers();
	myhtml_header(NULL);
	/* myhtml_banner(); */

	/* showenv(); */

	tmpl_render(t, data);
	myhtml_footer();

	mobject_free(data);
	params_free(ps);


	return EXIT_SUCCESS;
}
