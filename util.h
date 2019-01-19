/* include <dirent.h> before this file */

void 		http_headers();
int 		is_md     (struct dirent *);
int 		nlog      (const char *,...);
void 		redirect (char *);
int 		self_redirect(char *, char *, char *);
int 		my_read_file(char *, char **);
void 		printsep ();
int 		cat_strings(char **, int,...);
