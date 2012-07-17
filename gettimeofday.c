#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/time.h>
#include <assert.h>

int main(int argc, char *argv[])
{
	int ret;
	struct timeval tv;

	ret = gettimeofday(&tv, NULL);
	assert(ret == 0);

	return 0;
}
