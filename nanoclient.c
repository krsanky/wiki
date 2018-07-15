#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "settings.h"

void
fatal(const char *func)
{
	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
	exit(1);
}

int
client(const char *url)
{
	int 		sz_date = strlen("DATE") + 1;	/* '\0' too */
	char           *buf = NULL;
	int 		bytes = -1;
	int 		sock;
	int 		rv;

	if ((sock = nn_socket(AF_SP, NN_REQ)) < 0) {
		fatal("nn_socket");
	}
	if ((rv = nn_connect(sock, url)) < 0) {
		fatal("nn_connect");
	}
	printf("NODE1: SENDING DATE REQUEST\n");
	if ((bytes = nn_send(sock, "DATE", sz_date, 0)) < 0) {
		fatal("nn_send");
	}
	if ((bytes = nn_recv(sock, &buf, NN_MSG, 0)) < 0) {
		fatal("nn_recv");
	}
	printf("NODE1: RECEIVED DATE %s\n", buf);
	nn_freemsg(buf);
	return (nn_shutdown(sock, rv));
}

int
main(int argc, char **argv)
{
	printf("I am %s\n", argv[0]);

	if (client(SERVER_URL) < 0)
		fatal("nn error\n");

	return 0;
}



