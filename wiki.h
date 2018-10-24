void 		fatal    (const char *);
void 		http_headers(void);
void 		showenv  (void);

void 		testpage (void);
void 		errpage  (char *);
void 		msgpage  (char *);

void 		wikiindex(char *);
void 		wikiview (char *, char *);
void 		wikiedit (char *, char *);
void 		wikieditform();
void 		wikinew  (char *, char *);
char           *parse_boundary(char *);
