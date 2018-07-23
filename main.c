#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "wiki.h"
#include "myhtml.h"
#include "yuarel.h"


int 
main(void)
{
	FILE *logfile;
	struct yuarel_param *params;
	int p;
	params = malloc(sizeof(*params)*10); 

	if (params == NULL) {
		puts("error with malloc");
		return EXIT_FAILURE;
	}

	if ((logfile = fopen("log.txt", "a")) == NULL) {
		puts("error opening file");
		return EXIT_FAILURE;
	}

	fprintf(logfile, "main...\n");
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
	} else if(strcmp(params[0].key, "logtest")==0)  {
		wikilog("test...");
		msgpage("logtest");
	} else {
		query_params_test(params, 10);
	}

	if (logfile != NULL) fclose(logfile);
	return EXIT_SUCCESS;
}

