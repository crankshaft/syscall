#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/sendfile.h>

#ifndef SEND_TO_FILE
void set_addr(struct sockaddr_in *addr_in, const char *addr, u_short port)
{
    memset((void *)addr_in, 0, sizeof(struct sockaddr_in));
    addr_in->sin_port           = htons(port);
    addr_in->sin_family         = AF_INET;
    addr_in->sin_addr.s_addr    = inet_addr(addr);
}
#endif

int main(int argc, char *argv[])
{
	int in, out;
	ssize_t sz;

	in = open("./sendfile.c", O_RDONLY);

#ifdef SEND_TO_FILE
	out = open("./foo.out", O_WRONLY);
#else
	int ret;
	struct sockaddr_in addr;

	out = socket(AF_INET, SOCK_STREAM, 0);
	assert(out > 0);
	set_addr(&addr, "127.0.0.0", 8080);
	ret = connect(out, (const struct sockaddr *)&addr, sizeof(struct sockaddr_in));
	if (ret != 0) {
		perror("connect");
	}
	assert(ret == 0);
#endif
	assert(in>0 && out>0);

	sz = sendfile(out, in, 0, 512);
	if (sz < 0) {
		perror("sendfile");
		return 1;
	}
	printf("%d\n", sz);
	close(in);
	close(out);

	return 0;
}
