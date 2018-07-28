#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char   **environ;

int
              //
main(int argc, char *argv[])
{
	main(void) {
		/*
		puts is simpler than printf but be aware that the former automatically
		appends a newline.  If that's not what you want, you can fputs your
		string to stdout or use printf.
		*/
		if (-1 == pledge("stdio", NULL))
			err(EXIT_FAILURE, "pledge");
		//printf("Status: 200 OK\r\n");
		puts("Status: 200 OK\r");
		puts("Content-Type: text/html\r");
		puts("\r");
		puts("<!DOCTYPE HTML>");
		puts("<html>");
		puts("<body>");
		puts("<pre>");


		char           *data = getenv("QUERY_STRING");
		if (data == NULL)
			printf("Error! Error in passing data from form to script.\n");
		else
			printf("QUERY_STRING[%s]\n", data);

		puts("---------------");

		for (char **env = environ; *env; ++env)
			printf("%s\n", *env);


		puts("</pre>");
		puts("</body>");
		puts("</html>");
		return EXIT_SUCCESS;
	}
}
