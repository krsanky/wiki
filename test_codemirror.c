#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <mtemplate.h>

#include "wiki.h"
#include "forms.h"
#include "util.h"
#include "myhtml.h"
#include "tmpl.h"

/*
 * This is where the myhtml_header_add* stuff started 
 */
int
main()
{
	int 		ret;
	struct mobject *data;

	if (strcmp(getenv("REQUEST_METHOD"), "POST") == 0) {
		nlog("test_codemirror POST");
	}
	if ((data = myhtml_data_new()) == NULL) {
		errpage("err mdict_new()");
		return EXIT_FAILURE;
	}
	http_headers();

	myhtml_header_add_css(data, "/static/codemirror-5.46.0/lib/codemirror.css");
	myhtml_header_add_css(data, "/static/codemirror-5.46.0/addon/dialog/dialog.css");
	myhtml_header_add_css(data, "/static/codemirror-5.46.0/theme/midnight.css");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/lib/codemirror.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/addon/dialog/dialog.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/addon/search/searchcursor.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/addon/edit/matchbrackets.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/keymap/vim.js");
	myhtml_header_add_js(data, "/static/codemirror-5.46.0/keymap/emacs.js");
	myhtml_header(data);

	ret = tmpl_render("templates/test_codemirror.m", data);
	printf("<script>console.log('tmpl_render() ret:%d');</script>\n", ret);


	//showenv();

	myhtml_footer(data);

	mobject_free(data);
	return EXIT_SUCCESS;
}
