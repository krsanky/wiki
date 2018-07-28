#ifndef WIKI_H
#define WIKI_H

#include "yuarel.h"

void 		fatal    (const char *);
int 		build_html_file_list(char **, int);
void 		showenv  ();
void 		mainpage ();
void 		errorpage(char *);
void 		msgpage  (char *);
void 		query_params_test(struct yuarel_param *, int);
int 		wikilog   (char *);
void 		wikiindex(void);

#endif
