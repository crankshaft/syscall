#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int in, out;
	ssize_t sz;
	struct sockaddr_in ai;
	int pp[2];

	pipe(pp);

	in = open("./splice_to_sock.c", O_RDONLY);
	out = socket(AF_INET, SOCK_STREAM, 0);
	if (in < 0 || out < 0) {
		printf("open error\n");
		return 1;
	}

	memset(&ai, 0, sizeof(struct sockaddr_in));
	ai.sin_port = htons(8888);
	ai.sin_family = AF_INET;
	ai.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(out, (struct sockaddr *)&ai, sizeof(struct sockaddr_in)) != 0) {
		perror("connect");
		return;
	}

	sz = splice(in, 0, pp[1], 0, 4096, 0);
	if (sz < 0) {
		perror("splice");
		return 1;
	}

	printf("%d\n", sz);

	sz = splice(pp[0], 0, out, 0, 4096, 0);
	if (sz < 0) {
		perror("splice");
		return 1;
	}

	printf("%d\n", sz);

	close(in);
	close(out);
}
