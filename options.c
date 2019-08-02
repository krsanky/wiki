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

void
setup_cookie_page_var(char *name, PARAMS *cks, struct mobject *page_data)
{
	char           *val;

	nlog("setup_cookie_page_var");
	val = params_get(cks, name);
	nlog("setup_cookie_page_var 37");
	if (val == NULL)
		mdict_insert_ss(page_data, name, UNDEFINED);
	else
		mdict_insert_ss(page_data, name, val);
}

void
setup_data(char **names, int namesl, PARAMS * cks, struct mobject * page_data)
{
	for (int i=0; i<namesl; i++) {
		nlog("setup_data: name:%s", names[i]);
		setup_cookie_page_var(names[i], cks, page_data);
	}
	nlog("leave setup_data");
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
	int 		CL;
	int 		bufl;
	int 		ret;
	int 		i;
	char           *modify_var_name;
	char           *modify_var;

	char           *page_vars[] = {
		"editor",
		"bogus_var1",
		"cookie",
		"c1"
	};

	assert((data = mdict_new()) != NULL);
	assert((cps = params_new(5)) != NULL);

	if ((cookie = getenv("HTTP_COOKIE")) != NULL) {
		mdict_replace_ss(data, "cookie", cookie);
		ret = params_parse_http_cookie(cookie, cps);
		nlog("ret:%d", ret);
	}
	if (cps != NULL) {
		nlog("(cookie params) cps != NULL");
		for (i = 0; i < cps->len; i++) {
			nlog("key:%s", cps->params[i].key);
		}
	}
	
	setup_data(page_vars, 4, cps, data);

	if (strcasecmp(getenv("REQUEST_METHOD"), "POST") == 0) {
		qs = getenv("QUERY_STRING");
		assert(qs != NULL);
		CL_ = getenv("CONTENT_LENGTH");
		CL = (CL_ != NULL) ? atoi(CL_) : -1;
		
		nlog("CL:%d", CL);
		if (CL != -1) 
		{
			buf = malloc(CL);
			assert(buf != NULL);

			bufl = fread(buf, 1, CL, stdin);
			nlog("buf:%s", buf);
			assert((ps = params_create(5, buf)) != NULL);
			free(buf);

			modify_var_name = params_get(ps, "modify_var_name");
			modify_var = params_get(ps, params_get(ps, "modify_var_name"));
			if ((modify_var_name != NULL) && (modify_var != NULL)) {
				nlog("set_cookie(%s, %s)", modify_var_name, modify_var);
				set_cookie(modify_var_name, modify_var);
			}

			/* redir after POST */
			redirect("/options.cgi");
		}
	}

	http_headers();
	myhtml_header(NULL);
	myhtml_bannerA();
	tmpl_render(t, data);
	myhtml_footer();

	mobject_free(data);
	params_free(ps);
	params_free(cps);

	return EXIT_SUCCESS;
}
