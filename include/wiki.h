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

void 		fatal    (const char *);
void 		http_headers(void);
void 		showenv  (void);

void 		errpage  (char *,...);
void 		msgpage  (char *,...);

int 		make_mobject_dirlist(char *, struct mobject **);
void 		wikiindex(char *);
void 		wikiindex2(char *);
void 		wikiview (char *, char *);

void 		wikiedit (char *, char *);
void 		wikieditform();

void 		wikinew  (char *);
void 		wikinewform();
void 		wikinewdir(char *);
void 		wikinewdirform();

void 		wikidelete(char *, char *);
void 		wikioptions();

void		wikimove(char *, char *);

