#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "settings.h"
#include "util.h"

FILE           *logfile;

char           *
date(void)
{
	time_t 		now = time(&now);
	struct tm      *info = localtime(&now);
	char           *text = asctime(info);
	text[strlen(text) - 1] = '\0';	/* remove '\n' */
	return text;
}

void
dispatch(char *msg, int sock)
{
	int 		bytes;

	if (strcmp(msg, "DATE") == 0) {
		char           *d = date();
		int 		sz_d = strlen(d) + 1;
		printf("NODE0: SENDING  %s\n", d);
		if ((bytes = nn_send(sock, d, sz_d, 0)) < 0) {
			nn_fatal("nn_send");
		}
	} else if (strncmp(msg, LOG_PREFIX, sizeof(LOG_PREFIX) - 1) == 0) {
		if ((bytes = nn_send(sock, "RCVD", 5, 0)) < 0) {
			nn_fatal("nn_send");
		}
		msg = msg + sizeof(LOG_PREFIX) - 1;
		fprintf(logfile, "%s\n", msg);
		fflush(logfile);
	} else {
		if ((bytes = nn_send(sock, "RCVD", 5, 0)) < 0) {
			nn_fatal("nn_send");
		}
		fprintf(logfile, "UNKNOWN REQUEST:%s\n", msg);
		fflush(logfile);
	}
}

int
server(const char *url)
{
	int 		sock;
	int 		rv;

	if ((sock = nn_socket(AF_SP, NN_REP)) < 0) {
		nn_fatal("nn_socket");
	}
	if ((rv = nn_bind(sock, url)) < 0) {
		nn_fatal("nn_bind");
	}
	for (;;) {
		char           *msg = NULL;
		int 		bytes;
		if ((bytes = nn_recv(sock, &msg, NN_MSG, 0)) < 0) {
			nn_fatal("nn_recv");
		}
		printf("msg:%s\n", msg);
		/*
				fprintf(logfile, "msg:%s\n", msg);
				fflush(logfile);
		*/

		/*
		 * since nm allocated the buffer we won't check its length
		 * against bytes?
		 */
		dispatch(msg, sock);
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
	printf("I am %s argc:%d\n", argv[0], argc);


	logfile = fopen("nlog.txt", "a");
	if (logfile == NULL) {
		printf("error opening logfile\n");
		exit(1);
	}
	/*
		fprintf(logfile, "main...\n");
		fflush(logfile);
	*/

	server(SERVER_ENDPOINT);

	if (logfile != NULL)
		fclose(logfile);
	return 0;
}
