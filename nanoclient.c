#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "settings.h"
#include "util.h"

int
client()
{
	int 		sz_date = strlen("DATE") + 1;	/* '\0' too */
	char           *buf = NULL;
	int 		bytes = -1;
	int 		sock;
	int 		rv;

	if ((sock = nn_socket(AF_SP, NN_REQ)) < 0) {
		nn_fatal("nn_socket");
	}
	if ((rv = nn_connect(sock, SERVER_ENDPOINT)) < 0) {
		nn_fatal("nn_connect");
	}
	printf("NODE1: SENDING DATE REQUEST\n");
	if ((bytes = nn_send(sock, "DATE", sz_date, 0)) < 0) {
		nn_fatal("nn_send");
	}
	if ((bytes = nn_recv(sock, &buf, NN_MSG, 0)) < 0) {
		nn_fatal("nn_recv");
	}
	printf("NODE1: RECEIVED DATE %s\n", buf);
	nn_freemsg(buf);
	return (nn_shutdown(sock, rv));
}

int
main(int argc, char **argv)
{
	printf("I am %s argc:%d\n", argv[0], argc);

	if (client() < 0)
		nn_fatal("nn error\n");

	return 0;
}
