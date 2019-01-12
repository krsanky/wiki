#include <dirent.h>

int 		is_md     (struct dirent *);
int 		nlog      (const char *,...);
int 		wikilog   (char *);
void 		redirect (char *);
int 		self_redirect(char *, char *, char *);
int 		my_read_file(char *, char **);
void 		printsep ();
int 		cat_strings(char **, int,...);
