#include <dirent.h>

void 		nn_fatal (const char *);
int		is_md(struct dirent *);
int 		nlog      (const char *,...);
int 		wikilog   (char *);
void		redirect(char *);
int		ishex(int);
int		urldecode(const char *, char *);


