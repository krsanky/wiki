#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	printf("argc:%d %s\n", argc, argv[0]);
	char           *string, *found;

	string = strdup("Hello&there,&peasants!");
	printf("Original string: '%s'\n", string);

	while ((found = strsep(&string, "&")) != NULL)
		printf("%s\n", found);

	return (0);
}
