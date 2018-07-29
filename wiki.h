#ifndef WIKI_H
#define WIKI_H

#include "yuarel.h"

void 		fatal    (const char *);
void 		http_headers(void);
void 		showenv  (void);
void 		mainpage (void);
void 		errpage  (char *);
void 		msgpage  (char *);
void 		query_params_test(struct yuarel_param *, int);
int 		nlog      (const char *,...);
int 		wikilog   (char *);
void 		wikiindex(void);
void 		wikiview (char *);
char           *get_param(char *, struct yuarel_param *, int);

#endif
