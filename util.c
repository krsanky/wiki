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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <dirent.h>

#include "settings.h"

#include "util.h"

void
http_headers()
{
	printf("Content-type: text/html\n\n");
}

int
is_md(struct dirent * de)
{
	char           *ext;
	ext = strrchr(de->d_name, '.');
	if (ext != NULL) {
		ext++;
		if (strcasecmp(ext, "md") == 0)
			if (de->d_type == DT_REG)
				return 1;
	}
	return 0;
}

void
nn_fatal(const char *func)
{
	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
	exit(1);
}

int
wikilog(char *msg)
{
	char 		LOG_PREFIX[] = "LOG";
	char           *msg_;
	int 		msg_l;
	char           *buf;
	int 		bytes = -1;
	int 		sock;
	int 		rv;

	if ((sock = nn_socket(AF_SP, NN_REQ)) < 0) {
		nn_fatal("nn_socket");
	}
	if ((rv = nn_connect(sock, SERVER_ENDPOINT)) < 0) {
		nn_fatal("nn_connect");
	}
	msg_l = strlen(msg) + sizeof(LOG_PREFIX);
	msg_ = malloc(msg_l);
	strlcpy(msg_, LOG_PREFIX, msg_l);
	strlcat(msg_, msg, msg_l);

	if ((bytes = nn_send(sock, msg_, strlen(msg_) + 1, 0)) < 0) {
		nn_fatal("nn_send");
	}
	if ((bytes = nn_recv(sock, &buf, NN_MSG, 0)) < 0) {
		nn_fatal("nn_recv");
	}
	free(msg_);
	nn_freemsg(buf);
	return (nn_shutdown(sock, rv));
}

int
nlog(const char *fmt,...)
{
	char           *p;
	va_list 	ap;
	int 		ret;

	if ((p = malloc(256)) == NULL)
		return 0;
	va_start(ap, fmt);
	ret = vsnprintf(p, 256, fmt, ap);

	va_end(ap);
	ret = wikilog(p);
	free(p);
	return ret;
}

void
redirect(char *url)
{
	printf("Status: 302 Moved\r\nLocation: %s\r\n\r\n", url);
}
int
self_redirect(char *main, char *dir, char *page)
{
	int 		redirl;
	char           *redir;

	redirl = strlen("/wiki.cgi?") + strlen(main) + 1;
	if (dir != NULL)
		redirl += strlen(dir) + strlen("d=&");
	if (page != NULL)
		redirl += strlen(page) + strlen("p=&");
	nlog("self_redirect(): main:%s dir:%s page:%s redirl:%d", main, dir, page, redirl);
	if ((redir = malloc(redirl)) != NULL) {
		strlcpy(redir, "/wiki.cgi?index&", redirl);
		if (dir != NULL) {
			strlcat(redir, "d=", redirl);
			strlcat(redir, dir, redirl);
			strlcat(redir, "&", redirl);
		}
		if (page != NULL) {
			strlcat(redir, "p=", redirl);
			strlcat(redir, page, redirl);
			strlcat(redir, "&", redirl);
		}
		nlog("redir:%s", redir);
		redirect(redir);
		return 0;
	}
	return 1;
}

/*
 * caller responsible for freeing contents
 */
int
my_read_file(char *f, char **contents)
{
	FILE           *pfile;
	long 		numbytes;
	char           *buf = NULL;

	if (f == NULL)
		return -1;

	if ((pfile = fopen(f, "r")) == NULL) {
		/* exit_err("error opening file"); */
		return -1;
	}
	fseek(pfile, 0L, SEEK_END);
	numbytes = ftell(pfile);
	/* printf("num bytes:%ld\n", numbytes); */

	/* reset */
	fseek(pfile, 0L, SEEK_SET);

	buf = malloc(numbytes + 1);
	if (buf == NULL) {
		/* exit_err("malloc"); */
		return -1;
	}
	fread(buf, 1, numbytes, pfile);
	buf[numbytes] = '\0';	/* make sure there is a closing nul */
	/*
	 * printf("file:\n%s\n", buf); free(buf);
	 */
	if (pfile != NULL)
		fclose(pfile);

	*contents = buf;
	return 0;
}

void
printsep()
{
	printf("-----------------------------------------------------------------------\n");
}

/*
 * returns 0 on success.
 * caller needs to free buf if successful.
 */
int
cat_strings(char **buf, int nargs,...)
{
	char           *v;
	va_list 	ap;
	int 		len = 0;

	va_start(ap, nargs);
	for (int i = 0; i < nargs; i++) {
		v = va_arg(ap, char *);
		len += strlen(v);
	}
	len += 1;
	va_end(ap);

	if ((*buf = malloc(len)) == NULL)
		return -1;
	strlcpy(*buf, "", len);

	va_start(ap, nargs);
	for (int i = 0; i < nargs; i++)
		strlcat(*buf, va_arg(ap, char *), len);
	va_end(ap);

	return 0;
}
