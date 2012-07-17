#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	errno = atoi(argv[1]);
	perror("err");
	return 0;
}
