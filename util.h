#include <dirent.h>

void		nn_fatal(const char *);
int		is_md(struct dirent *);
int		nlog(const char *,...);
int		wikilog(char *);
void		redirect(char *);
int		my_read_file(char *, char **);
int		my_write_file(char *, char *, int);
void		printsep();

