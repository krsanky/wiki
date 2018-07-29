#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <dirent.h>
#include <unistd.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>
#include <mkdio.h>

#include "wiki.h"
#include "myhtml.h"
#include "yuarel.h"
#include "settings.h"

extern char   **environ;

void
fatal(const char *func)
{
	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
	exit(1);
}

void
http_headers(void)
{
	printf("Content-type: text/html\n\n");
}

void
query_params_test(struct yuarel_param * params, int sz)
{
	char           *qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errpage("error with QUERY_STRING");
		return;
	}
	if (sz < 0) {
		errpage("error with yuarel_parse_query()");
		return;
	}
	http_headers();

	myhtml_header();
	myhtml_topnav();
	printf("<dl>\n");
	while (sz-- > 0) {
		printf("<dt>%s</dt><dd>%s</dd>\n", params[sz].key, params[sz].val);
	}
	printf("</dl>\n");

	myhtml_footer();
}

void
mainpage(void)
{
	http_headers();

	myhtml_header();
	myhtml_topnav();
	printf("\
<p>wiki wiki wiki</p>\n\
<ul>\n\
<li><a href='/wiki.cgi?index'>index</a></li>\
</ul>\n");

	showenv();

	myhtml_footer();
}

void
errpage(char *error)
{
	http_headers();

	myhtml_header();
	myhtml_topnav();
	printf("\
<p style='color:red;'>%s</p>\n", error);
	myhtml_footer();
}

void
msgpage(char *msg)
{
	http_headers();

	myhtml_header();
	myhtml_topnav();
	printf("\
<p style='color:green;'>%s</p>\n", msg);
	myhtml_footer();
}

void
showenv()
{
	printf("<pre>\n");
	char           *data = getenv("QUERY_STRING");
	if (data == NULL)
		printf("Error! Error in passing data from form to script.\n");
	else
		printf("QUERY_STRING[%s]\n", data);

	puts("---------------");

	for (char **env = environ; *env; ++env)
		printf("%s\n", *env);

	printf("</pre>\n");
}

/*
int
printf(const char *fmt, ...)
{
	int ret;
	va_list ap;

	va_start(ap, fmt);
	ret = vfprintf(stdout, fmt, ap);
	va_end(ap);
	return (ret);
}

           #include <stdarg.h>
           #include <stdio.h>
           #include <stdlib.h>

           char *
           newfmt(const char *fmt, ...)
           {
                   char *p;
                   va_list ap;

                   if ((p = malloc(128)) == NULL)
                           return (NULL);
                   va_start(ap, fmt);
                   (void) vsnprintf(p, 128, fmt, ap);
                   va_end(ap);
                   return (p);
           }
*/
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

int
wikilog(char *msg)
{
	char           *msg_;
	int 		msg_l;
	char           *buf;
	int 		bytes = -1;
	int 		sock;
	int 		rv;

	if ((sock = nn_socket(AF_SP, NN_REQ)) < 0) {
		fatal("nn_socket");
	}
	if ((rv = nn_connect(sock, SERVER_ENDPOINT)) < 0) {
		fatal("nn_connect");
	}
	msg_l = strlen(msg) + sizeof(LOG_PREFIX);
	msg_ = malloc(msg_l);
	strlcpy(msg_, LOG_PREFIX, msg_l);
	strlcat(msg_, msg, msg_l);

	if ((bytes = nn_send(sock, msg_, strlen(msg_) + 1, 0)) < 0) {
		fatal("nn_send");
	}
	if ((bytes = nn_recv(sock, &buf, NN_MSG, 0)) < 0) {
		fatal("nn_recv");
	}
	free(msg_);
	nn_freemsg(buf);
	return (nn_shutdown(sock, rv));
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
wikiindex(void)
{
	struct dirent  *de;
	DIR            *dir;


	dir = opendir(WIKI_ROOT);
	if (dir == NULL) {
		errpage("could not open dir:");
	}
	http_headers();
	myhtml_header();
	myhtml_topnav();
	printf("<ul>\n");
	while ((de = readdir(dir)) != NULL) {
		if (is_md(de)) {
			printf("\
<li>\
<a href='/wiki.cgi?view&p=%s'>\
%s\
</a></li>\n", de->d_name, de->d_name);
		} else if (de->d_type == DT_DIR) {
			printf("\
<li>\
<a href='/wiki.cgi?index&d=%s'>\
dir:%s\
</a></li>\n", de->d_name, de->d_name);
		}
	}
	printf("</ul>\n");
	myhtml_footer();

	closedir(dir);
}


void
wikiview(char *filename)
{
	int 		val;
	MMIOT          *mmiot;
	FILE           *mdfile;
	char           *fullpath;
	int 		fpl;

	fpl = sizeof(WIKI_ROOT) + 1 + strlen(filename);
	fullpath = malloc(fpl);
	strlcpy(fullpath, WIKI_ROOT, fpl);
	strlcat(fullpath, "/", fpl);
	strlcat(fullpath, filename, fpl);


	mdfile = fopen(fullpath, "r");
	free(fullpath);
	if (mdfile == NULL) {
		errpage("cannot open input file:");
	}
	mmiot = mkd_in(mdfile, 0);

	http_headers();
	myhtml_header();
	myhtml_topnav();
	val = markdown(mmiot, stdout, MKD_GITHUBTAGS);
	myhtml_footer();
	/* val ???? */

	if (mdfile != NULL)
		fclose(mdfile);
}

char           *
get_param(char *pname, struct yuarel_param * params, int sz)
{
	char           *msg;
	int 		msgl;
	msgl = strlen("this is the msg mdfile:") + strlen(pname) + 1;
	msg = malloc(msgl);
	if (msg != NULL) {
		strlcpy(msg, "this is the msg:", msgl);
		strlcat(msg, pname, msgl);
		wikilog(msg);
	}
	for (int i = 0; i < sz; i++) {

	}
	return NULL;
}
