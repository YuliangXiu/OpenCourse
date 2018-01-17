
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*sighandler_t)(int);

void sigcatch() {
	printf("%d 号进程继续运行！From：sigcat\n", getpid());
}
