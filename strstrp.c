#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * caller responsible for freeing returned pointer.
 */
int
my_read_file(char *f, char **contents)
{
	FILE	       *pfile;
	long		numbytes;
	char	       *buf = NULL;

	if (f == NULL)
		return -1;
	if ((pfile = fopen(f, "r")) == NULL) {
		return -1;
	}
	fseek(pfile, 0L, SEEK_END);
	numbytes = ftell(pfile);
	/* printf("num bytes:%ld\n", numbytes); */

	/* reset */
	fseek(pfile, 0L, SEEK_SET);

	buf = malloc(numbytes + 1);
	if (buf == NULL) {
		/* exit_err("malloc"); */
		return -1;
	}
	fread(buf, 1, numbytes, pfile);
	buf[numbytes] = '\0';	/* make sure there is a closing nul */
	if (pfile != NULL)
		fclose(pfile);

	*contents = buf;
	return 0;
}

int
main(void)
{
	char	       *fn = "searchstring.txt";
	char	       *b = "wd123qwdqwd123qwdqwd";
	int		r;
	char	       *s1;
	char	       *txt = NULL;

	r = my_read_file(fn, &txt);
	printf("txt:\n%.25s...\n\n", txt);

	s1 = txt;
	while ((s1 = strstr(s1, b)) != NULL) {
		printf("strstr:\n%.45s\n", s1);
		s1 += 1;
	}

	free(txt);
	return EXIT_SUCCESS;
}