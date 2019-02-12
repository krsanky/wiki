#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *
return_str()
{
	char		s1[] = "test string...";
	char		*s2;

	if ((s2 = malloc(strlen(s1)+1)) == NULL)
		return NULL;

	strlcpy(s2, s1, strlen(s1)+1);

	return s2;
}

void
modify_param_str(char ** buf, int bufl)
{
	char		s1[] = "test string...modify";
	strlcpy(*buf, s1, bufl+1);
}

int
main()
{
	char		*s3;

	/* */
	printf("test strings\n");  
	s3 = return_str();
	printf("s3:%s\n", s3);
	free(s3);
	free(NULL);
	
	/* */
	char * buf;
	if ((buf = malloc(10)) == NULL) {
		printf("malloc error\n");
		return EXIT_FAILURE;
	}
	modify_param_str(&buf, 10);
	printf("buf:%s\n", buf);
	free(buf);

	return EXIT_SUCCESS;
}



