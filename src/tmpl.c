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

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

#include "params.h"
#include "mtemplate.h"
#include "myhtml.h"
#include "settings.h"

#include "tmpl.h"

/*
 * tbuf should be freed by caller.
 */
int
tmpl_readfile(char *filename, char **tbuf)
{
	int 		tfd;
	size_t 		tlen = 0;
	int 		len = 0;
	char 		buf      [8192];

	if ((tfd = open(filename, O_RDONLY)) == -1) {
		return -1;
	}
	for (;;) {
		if ((len = read(tfd, buf, sizeof(buf))) == -1) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			return -1;
		}
		if (len == 0) {
			break;
		}
		if (tlen + len + 1 < tlen) {
			/* errx(1, "template length exceeds SIZE_T_MAX"); */
			return -1;
		}
		if ((*tbuf = realloc(*tbuf, tlen + len + 1)) == NULL) {
			return -1;
		}
		memcpy(*tbuf + tlen, buf, len);
		*(*tbuf + tlen + len) = '\0';
		tlen += len;
	}
	close(tfd);
	/* printf("\nraw templ.\n:<pre>\n%s\n</pre>\n", *tbuf); */

	return 0;
}

int
tmpl_render(char *tmplfn, struct mobject * namespace)
{
	int 		ret;
	char           *tbuf = NULL;
	struct mtemplate *t = NULL;

	ret = tmpl_readfile(tmplfn, &tbuf);
	if (ret != 0) {
		/* printf("error ret:%d\n", ret); */
		goto end;
	}
	/* parse-and-cache ? */
	if ((t = mtemplate_parse(tbuf, NULL, 0)) == NULL) {
		/* mtemplate_parse error */
		ret = -2;
		goto end;
	}
	ret = mtemplate_run_stdio(t, namespace, stdout, NULL, 0);
	if (ret == -1) {
		/* error mtemplate_run_stdio */
		goto end;
	}
	ret = 0;
end:
	free(tbuf);
	if (t == NULL)
		mtemplate_free(t);
	return ret;
}

char           *
tmpl_path(char *t)
{
	int 		l = 0;
	char           *tp;

	l += strlen(WIKI_ROOT);
	l += strlen("/");
	l += strlen(t);
	l += 1;

	if ((tp = malloc(l)) == NULL)
		return NULL;

	strlcpy(tp, WIKI_ROOT, l);
	strlcat(tp, "/", l);
	strlcat(tp, t, l);

	return tp;
}
