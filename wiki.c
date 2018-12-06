#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <mkdio.h>
#include <fcntl.h>

#include "wiki.h"
#include "myhtml.h"
#include "params.h"
#include "settings.h"
#include "util.h"
#include "forms.h"

extern char   **environ;


void
http_headers(void)
{
	printf("Content-type: text/html\n\n");
}

void
testpage(void)
{
	http_headers();

	myhtml_header();
	printf("\
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
	/* myhtml_topnav(NULL, NULL); */
	printf("\
<p style='color:red;'>%s</p>\n", error);
	myhtml_footer();
}

void
msgpage(char *msg)
{
	http_headers();

	myhtml_header();
	/* myhtml_topnav(NULL, NULL); */
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


void
wikiindex(char *dir_)
{
	struct dirent  *de;
	DIR            *dir;
	int 		dirl = 0;
	char           *fulldir;

	if (dir_ == NULL) {
		fulldir = WIKI_ROOT;
	} else {
		dirl = sizeof(WIKI_ROOT) + strlen(dir_) + 1;
		fulldir = malloc(dirl);
		strlcpy(fulldir, WIKI_ROOT, dirl);
		strlcat(fulldir, "/", dirl);
		strlcat(fulldir, dir_, dirl);
	}
	nlog("dir_:%s fulldir:%s", dir_, fulldir);

	/* need to see if fulldir exists before attempt to open */
	int test = open(fulldir, O_DIRECTORY);
	if (test < 0) {
		errpage("could not open dir:");
		return;
	}
	close(test);

	dir = opendir(fulldir);
	if (dir == NULL) {
		errpage("could not open dir:");
	}
	if (dirl > 0)
		free(fulldir);

	http_headers();
	myhtml_header();
	/* myhtml_topnav(dir_, NULL); */
	myhtml_breadcrumbs(dir_, NULL, NULL);
	printf("<ul>\n");
	while ((de = readdir(dir)) != NULL) {
		if (is_md(de)) {
			if (dir_ == NULL) {
				printf("\
<li>\
<a href='/wiki.cgi?view&p=%s'>\
%s\
</a></li>\n", de->d_name, de->d_name);
			} else {
				printf("\
<li>\
<a href='/wiki.cgi?view&d=%s&p=%s'>\
%s\
</a></li>\n", dir_, de->d_name, de->d_name);

			}

		} else if ((de->d_type == DT_DIR) && (de->d_name[0] != '.')) {
			if (dir_ == NULL) {
				printf("\
<li>\
<a href='/wiki.cgi?index&d=%s'>\
dir:%s\
</a></li>\n", de->d_name, de->d_name);
			} else {
				printf("\
<li>\
<a href='/wiki.cgi?index&d=%s/%s'>\
dir:%s\
</a></li>\n", dir_, de->d_name, de->d_name);
			}
		}
	}
	printf("</ul>\n");
	myhtml_footer();

	closedir(dir);
}


void
wikiview(char *dir, char *page)
{
	int 		val;
	MMIOT          *mmiot;
	FILE           *mdfile;
	char           *fullpath;
	int 		fpl;

	nlog("here in wikiview(%s, %s)", dir, page);
	fpl = sizeof(WIKI_ROOT) + 1 + strlen(page);
	if (dir != NULL)
		fpl = fpl + strlen(dir) + 1;
	fullpath = malloc(fpl);
	strlcpy(fullpath, WIKI_ROOT, fpl);
	strlcat(fullpath, "/", fpl);
	if (dir != NULL) {
		strlcat(fullpath, dir, fpl);
		strlcat(fullpath, "/", fpl);
	}
	strlcat(fullpath, page, fpl);
	nlog("wikiview fullpath:%s", fullpath);

	mdfile = fopen(fullpath, "r");
	free(fullpath);
	if (mdfile == NULL) {
		errpage("cannot open input file:");
	}
	mmiot = mkd_in(mdfile, 0);

	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, page, "view");
	val = markdown(mmiot, stdout, MKD_GITHUBTAGS);
	myhtml_footer();

	if (mdfile != NULL)
		fclose(mdfile);
}

void
wikiedit(char *dir, char *page)
{
	int 		fpl;
	char           *fullpath;
	FILE           *mdfile;
	char 		c;

	fpl = sizeof(WIKI_ROOT) + 1 + strlen(page);
	if (dir != NULL)
		fpl = fpl + strlen(dir) + 1;
	fullpath = malloc(fpl);
	strlcpy(fullpath, WIKI_ROOT, fpl);
	strlcat(fullpath, "/", fpl);
	if (dir != NULL) {
		strlcat(fullpath, dir, fpl);
		strlcat(fullpath, "/", fpl);
	}
	strlcat(fullpath, page, fpl);
	nlog("wikiview fullpath:%s", fullpath);

	mdfile = fopen(fullpath, "r");
	free(fullpath);
	if (mdfile == NULL) {
		errpage("cannot open input file:");
		return;
	}
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, page, "edit");
	myhtml_textarea_open();

	while ((c = fgetc(mdfile)) != EOF) {
		printf("%c", c);
/*
		if (c == '\n')
			nlog("wikedit form \\n");
		if (c == '\r')
			nlog("wikedit form \\r");
*/
	}

	if (mdfile != NULL)
		fclose(mdfile);

	myhtml_textarea_close(dir, page);
	myhtml_footer();
}

/* This is being handled by wikieditform.php currently.
 *
 * This answers the POST from wikiedit.
 * This is the first form handling code.
 */
void
wikieditform()
{
	char           *RM;
	char           *CL_;
	char           *CT;
	int 		CL;
	/*char 		buf      [1024];*/
	char		*buf;
	int 		l = 0;
	char           *boundary;
	PARAM          *params;
	int		NPARAMS = 4;

	RM = getenv("REQUEST_METHOD");
	CL_ = getenv("CONTENT_LENGTH");
	CT = getenv("CONTENT_TYPE");
	if (CL_ != NULL)
		CL = atoi(CL_);
	else
		CL = -1;

	nlog("editform() RM[%s] CT[%s] CL[%d]", RM, CT, CL);

	nlog("pre parse_b...");
	boundary = parse_boundary(CT);
	nlog("post parse_b...");


/*
In my code, you see a lot of constructs where it's buf, offset, and
length.  The buf variable points to the start of the buffer and is
never incremented.  The length variable is the max length of the
buffer and likewise never changes.  It's the offset variable that
is incremented throughout.
*/

	params = malloc(sizeof(PARAM) * NPARAMS);
	params_initialize(params, NPARAMS);



	/* -- display -- */
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(NULL, NULL, "edit");







	buf = malloc(CL);
	/* try using CONTENT_LENGTH */
	if (buf != NULL) {
		l = fread(buf, 1, CL, stdin);
		params_parse_multipart_POST(buf, boundary, params, NPARAMS);
	}




	printf("<pre>\n");
	printf("boundary[%s]\n", boundary);
	printf("buf:\n%s\n", buf);
	printf("</pre>\n");

	printf("<hr/>\n");
	showenv();
	myhtml_footer();

	params_free(params, NPARAMS);
	free(boundary);
	free(buf);
	free(NULL);
}

void
wikinew(char *dir)
{
	http_headers();
	myhtml_header();
	myhtml_breadcrumbs(dir, NULL, "new");
	myhtml_new(dir);
	myhtml_footer();
}
void
wikinewform()
{
	char           *RM;
	char           *CL_;
	char           *CT;
	int 		CL;
	char		*buf;
	int		l;

	PARAM          *params;
	int		NPARAMS = 5;
	char		*page;
	char		*dir;

	RM = getenv("REQUEST_METHOD");
	CL_ = getenv("CONTENT_LENGTH");
	CT = getenv("CONTENT_TYPE");
	if (CL_ != NULL)
		CL = atoi(CL_);
	else
		CL = -1;

	nlog("wikinewform() RM[%s] CT[%s] CL[%d]", RM, CT, CL);

	buf = malloc(CL);
	if (buf != NULL) {
		l = fread(buf, 1, CL, stdin);
		nlog("buf:%s", buf);
		/*
		main.c main() QUERY_STRING:newform
		wikinewform() RM[POST] CT[application/x-www-form-urlencoded] CL[22]                                             
		buf:page=123qwd&dir=dir123
		*/
		params = malloc(sizeof(PARAM) * NPARAMS);
		params_initialize(params, NPARAMS);
		params_parse_query(buf, params, NPARAMS);

		page = params_get("page", params, NPARAMS);
		dir = params_get("dir", params, NPARAMS);
		nlog("make new file dir:%s page:%s", dir, page);


		/* this is 2nd use, maybe this could be a util method */
		char		*fullpath;
		FILE           *newfile;
		int		fpl;

		fpl = sizeof(WIKI_ROOT) + 1 + strlen(page);
		if (dir != NULL)
			fpl = fpl + strlen(dir) + 1;
		fullpath = malloc(fpl);
		strlcpy(fullpath, WIKI_ROOT, fpl);
		strlcat(fullpath, "/", fpl);
		if (dir != NULL) {
			strlcat(fullpath, dir, fpl);
			strlcat(fullpath, "/", fpl);
		}
		strlcat(fullpath, page, fpl);
		nlog("wikinewform:: fullpath:%s", fullpath);

		newfile = fopen(fullpath, "a");
		free(fullpath);
		if (newfile == NULL) {
			errpage("cannot create file:");
			return;
		}
		if (newfile != NULL)
			fclose(newfile);

		params_free(params, NPARAMS);

		/*redirect();*/
		msgpage("new file created");
		return;
	} 
		
	free(buf);
	errpage("error creating new file");
}

void
wikidelete(char *dir, char *page)
{
	char		*delpath;
	int		dpl = strlen(WIKI_ROOT) + 1 + 10; // eol and to not count slashes
	if (dir != NULL) 
		dpl += strlen(dir);
	if (page != NULL)
	 	dpl += strlen(page);
	nlog("WIKIDELETE dir:%s page:%si l:%d", dir, page, dpl);
	delpath = malloc(dpl);
	if (delpath != NULL) {
		strlcpy(delpath, WIKI_ROOT, dpl); 
		if (dir != NULL) {
			strlcat(delpath, "/", dpl); 
			strlcat(delpath, dir, dpl);
		}
		if (page != NULL) {
			strlcat(delpath, "/", dpl); 
			strlcat(delpath, page, dpl);
		}
		nlog("delpath:%s", delpath);
		unlink(delpath);
		free(delpath);
	}


	http_headers();
	myhtml_header();
	//myhtml_breadcrumbs(dir, page, NULL);
	printf("\
<h1>del p:%s d:%s</h1>\n", page, dir);
	myhtml_footer();
}


