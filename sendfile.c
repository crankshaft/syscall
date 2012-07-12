#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int in, out;
	ssize_t sz;

	in = open("./sendfile.c", O_RDONLY);
	out = open("./foo.out", O_WRONLY);
	if (in < 0 || out < 0) {
		printf("open file error\n");
		return 1;
	}

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
