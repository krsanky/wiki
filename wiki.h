#ifndef WIKI_H
#define WIKI_H

#include "yuarel.h"

void 		fatal    (const char *);
void 		showenv  (void);
void 		mainpage (void);
void 		errorpage(char *);
void 		msgpage  (char *);
void 		query_params_test(struct yuarel_param *, int);
int 		wikilog   (char *);
void 		wikiindex(void);

#endif
