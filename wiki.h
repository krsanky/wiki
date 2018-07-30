#include "yuarel.h"

void 		fatal    (const char *);
void 		http_headers(void);
void 		showenv  (void);
void 		mainpage (void);
void 		errpage  (char *);
void 		msgpage  (char *);
void 		query_params_test(struct yuarel_param *, int);
void 		wikiindex(char *);
void 		wikiview (char *, char *);
char           *get_param(char *, struct yuarel_param *, int);
