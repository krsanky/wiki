#ifndef WIKI_H
#define WIKI_H

#include "yuarel.h"

int build_html_file_list(char **, int);
void showenv();
void mainpage();
void errorpage(char *);
void msgpage(char *);
void query_params_test(struct yuarel_param *, int);
void wikilog(char *);

#endif
