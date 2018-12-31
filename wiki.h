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

void 		wikinew  (char *);
void 		wikinewform();

void 		wikidelete(char *, char *);

typedef struct wikilink {
	char 		url      [256];
	char 		name     [128];
} 		wlink;		/* better names? wlink Wlink Wikilink ? */
int 		get_wlinks(FILE *, wlink **);
int 		alpha_wlinks(wlink **);
