void 		fatal    (const char *);
void 		http_headers(void);
void 		showenv  (void);

void 		errpage  (char *);
void 		msgpage  (char *);

void 		wikiindex(char *);
void 		wikiindex2(char *);
void 		wikiview (char *, char *);

void 		wikiedit (char *, char *);
void 		wikieditform();

void 		wikinew  (char *);
void 		wikinewform();

void 		wikidelete(char *, char *);

typedef struct wikipage {
	char 		url      [256];
	char 		name     [128];
} 		Page;
int 		GetPages  (FILE *, Page **);
int 		AlphaPages(Page **);
