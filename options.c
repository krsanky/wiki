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

int 
main()
{
	char 		t        [] = "templates/options.m";
	struct mobject *data;
	PARAMS         *ps = NULL;
	char           *qs, *CL_, *buf;
	char           *var2;
	int 		CL;
	int 		bufl;

	assert((data = mdict_new()) != NULL);

	if (strcasecmp(getenv("REQUEST_METHOD"), "POST") == 0) {
		printf("Set-Cookie:ThisIsCookie123 = HeyTHisThingx;\r\n");
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

		var2 = params_get(ps, "var2");
		nlog("var2:%s", var2);
	}
	http_headers();
	myhtml_header(NULL);

/* 	showenv(); */

	tmpl_render(t, data);
	myhtml_footer();

	mobject_free(data);
	params_free(ps);


	return EXIT_SUCCESS;
}
