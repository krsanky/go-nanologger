#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <nanomsg/nn.h>
#include <nanomsg/reqrep.h>

#include "client.h"

void
nnclient_fatal(const char *func)
{
	fprintf(stderr, "%s: %s\n", func, nn_strerror(nn_errno()));
	exit(1);
}

int
nlog(const char *fmt,...)
{
	char	       *p;
	va_list		ap;
	int		ret;

	if ((p = malloc(256)) == NULL)
		return 0;
	va_start(ap, fmt);
	ret = vsnprintf(p, 256, fmt, ap);

	va_end(ap);
	ret = wikilog(p);
	free(p);
	return ret;
}

int
wikilog(char *msg)
{
	/* TODO: pass in port ? */
	char		*SERVER_ENDPOINT = "tcp://127.0.0.1:23000";
	char		*LOG_PREFIX = "LOG-";
	char	       *msg_;
	int		msg_l;
	char	       *buf;
	int		bytes = -1;
	int		sock;
	int		rv;

	if ((sock = nn_socket(AF_SP, NN_REQ)) < 0) {
		nnclient_fatal("nn_socket");
	}
	if ((rv = nn_connect(sock, SERVER_ENDPOINT)) < 0) {
		nnclient_fatal("nn_connect");
	}
	msg_l = strlen(msg) + sizeof(LOG_PREFIX);
	msg_ = malloc(msg_l);
	strlcpy(msg_, LOG_PREFIX, msg_l);
	strlcat(msg_, msg, msg_l);

	if ((bytes = nn_send(sock, msg_, strlen(msg_) + 1, 0)) < 0) {
		nnclient_fatal("nn_send");
	}
	if ((bytes = nn_recv(sock, &buf, NN_MSG, 0)) < 0) {
		nnclient_fatal("nn_recv");
	}
	free(msg_);
	nn_freemsg(buf);
	return (nn_shutdown(sock, rv));
}


