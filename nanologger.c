#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "settings.h"

FILE           *logfile;

void
fatal(const char *func)
{
	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
	exit(1);
}

char           *
date(void)
{
	time_t 		now = time(&now);
	struct tm      *info = localtime(&now);
	char           *text = asctime(info);
	text[strlen(text) - 1] = '\0'; /* remove '\n' */
	return text;
}

void
dispatch(char *msg, int sock)
{
	int bytes;
	fprintf(logfile, "RECEIVED REQUEST:%s\n", msg);
	if (strcmp(msg, "DATE") == 0) {
		char           *d = date();
		int 		sz_d = strlen(d) + 1;
		printf("NODE0: SENDING  %s\n", d);
		if ((bytes = nn_send(sock, d, sz_d, 0)) < 0) {
			fatal("nn_send");
		}
	} else {
		fprintf(logfile, "UNKNOWN REQUEST:%s\n", msg);
	}
}

int
server(const char *url)
{
	int 		sock;
	int 		rv;

	if ((sock = nn_socket(AF_SP, NN_REP)) < 0) {
		fatal("nn_socket");
	}
	if ((rv = nn_bind(sock, url)) < 0) {
		fatal("nn_bind");
	}
	for (;;) {
		char           *msg = NULL;
		int 		bytes;
		if ((bytes = nn_recv(sock, &msg, NN_MSG, 0)) < 0) {
			fatal("nn_recv");
		}
		fprintf(logfile, "msg:%s\n", msg);
		fflush(logfile);

		/*
		 * since nm allocated the buffer we won't check its length
		 * against bytes?
		 */
		dispatch(msg, sock);
		/*
		if ((bytes == (strlen("DATE") + 1)) && (strcmp("DATE",msg) == 0)) {
			printf("NODE0: RECEIVED  REQUEST\n");
			fprintf(logfile, "NODE0: RECEIVED  REQUEST\n");
			char           *d = date();
			int 		sz_d = strlen(d) + 1;
			printf("NODE0: SENDING  %s\n", d);
			if ((bytes = nn_send(sock, d, sz_d, 0)) < 0) {
				fatal("nn_send");
			}
		}
		*/


		nn_freemsg(msg);
	}
}

/*
 * All major routines should have a comment briefly describing what they do.
 * The comment before the "main" routine should describe what the program
 * does.
 */
int
main(int argc, char **argv)
{
	printf("I am %s\n", argv[0]);

	logfile = fopen("log.txt", "a");
	if (logfile == NULL) {
		printf("error opening logfile\n");
		exit(1);
	}
	fprintf(logfile, "main...\n");
	fflush(logfile);

	server(SERVER_URL);

	if (logfile != NULL)
		fclose(logfile);
	return 0;
}
