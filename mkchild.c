#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    pid_t pid;

    assert(argc > 0);

    if (argc < 2) {
        printf("usage: %s command [arguments...]\n", argv[0]);
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], argv + 1);
        perror(argv[1]);
        return 1;
    }

    assert(pid > 0);

    if (wait(NULL) != pid) {
        perror("wait");
        return 1;
    }

    return 0;
}
