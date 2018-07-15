#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wiki.h"
#include "myhtml.h"
#include "yuarel.h"

FILE *logfile;

int 
main(void)
{
	logfile = fopen("log.txt", "a");
	fprintf(logfile, "main...\n");
	int p;
	struct yuarel_param params[10];
	char *qs = getenv("QUERY_STRING");
	if (qs == NULL) {
		errorpage("error with QUERY_STRING");
		return EXIT_FAILURE;
	}
	if (strlen(qs) > 0) {
		p = yuarel_parse_query(qs, '&', params, 10);
		if (p < 0) {
			char * tmpstr = malloc(100);	
			if (tmpstr == NULL) {
				errorpage("error with yuarel_parse_query()");
			} else {
				snprintf(tmpstr, 99, "error with yuarel_parse_query() [QUERY_STRING:%s][len:%lu]", qs, strlen(qs));
				errorpage(tmpstr);
				free(tmpstr);
			}
			return EXIT_FAILURE;
		}
	}

	
	if ((strlen(qs) < 1) || (p < 1)) {
		mainpage();
	} else if(strcmp(params[0].key, "start")==0)  {
		errorpage("start");
	} else {
		query_params_test();
	}

	if (logfile != NULL) fclose(logfile);
	return EXIT_SUCCESS;
}

