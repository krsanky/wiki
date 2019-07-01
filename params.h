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

typedef struct param {
	char           *key;
	char           *val;
} 		PARAM;

typedef struct params {
	char           *query_string;
	int 		len;
	PARAM          *params;
} 		PARAMS;

PARAMS         *params_new(int);
PARAMS         *params_create(int, char *);
void 		params_free(PARAMS *);

int 		params_parse_query(char *, PARAMS *);
int 		params_parse_http_cookie(char *, PARAMS *);

int 		params_ishex(int);
int 		params_urldecode(char *, char *);
char           *params_get(PARAMS *, char *);

int 		params_testdb();
