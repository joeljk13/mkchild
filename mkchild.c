#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static pid_t pid;

static void
sigint(int sig)
{
    pid_t pg;

    assert(sig == SIGINT || sig == SIGTERM);

    pg = getpgid(pid);

    if (kill(-pg, SIGINT) < 0) {
        perror("kill");
    }
    usleep(1000);
    if (kill(-pg, 0) < 0 && errno == ESRCH) {
        return;
    }
    sleep(1);
    if (kill(-pg, SIGTERM) < 0) {
        if (errno == ESRCH) {
            return;
        }
        perror("kill");
    }
    usleep(1000);
    if (kill(-pg, 0) < 0 && errno == ESRCH) {
        return;
    }
    sleep(1);
    if (kill(-pg, SIGKILL) < 0) {
        if (errno == ESRCH) {
            return;
        }
        perror("kill");
    }
}

int
main(int argc, char **argv)
{
    const char *program_name;
    struct sigaction act;

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
        if (setpgid(pid, 0) < 0) {
            perror("setpgid");
            return 1;
        }
        execvp(argv[1], &argv[1]);
        perror(argv[1]);
        return 1;
    }

    memset(&act, 0, sizeof(act));
    act.sa_handler = sigint;
    act.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &act, NULL) < 0
        || sigaction(SIGTERM, &act, NULL) < 0) {
        perror("sigaction");
        return 1;
    }

    if (wait(NULL) != pid) {
        perror("wait");
        return 1;
    }

    return 0;
}
