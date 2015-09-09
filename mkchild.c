#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    pid_t pid;
    const char *program_name;

    if (argc >= 1) {
        program_name = argv[0];
    } else {
        program_name = "mkchild";
    }

    if (argc == 1) {
        printf("usage: %s command [arguments...]\n", program_name);
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        perror(argv[1]);
        return 1;
    }

    if (wait(NULL) != pid) {
        perror("wait");
        return 1;
    }

    return 0;
}
