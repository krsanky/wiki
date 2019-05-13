#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <mtemplate.h>

#include "forms.h"
#include "util.h"
#include "myhtml.h"
#include "tmpl.h"

void
display()
{
	char 		t        [] = "templates/menu.m";
	http_headers();
	myhtml_header(NULL);
	printf("<h1>menu</h1>\n");
	tmpl_render(t, NULL);
	myhtml_footer();
}

int
main()
{
	display();
	return EXIT_SUCCESS;
}
