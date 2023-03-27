#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/time.h>


void signal_handler(int signum) {
    printf("Received signal: %d\n", signum);
}

int main() {
    int i;

    // Set signal handlers for all signals
    for (i = 1; i <= 31; i++) {
        if (i == SIGKILL || i == SIGSTOP) {
            // These signals cannot be caught or ignored
            continue;
        }

        if (signal(i, signal_handler) == SIG_ERR) {
            perror("signal");
            return EXIT_FAILURE;
        }
    }

    // Generate each signal
    printf("Generating signals...\n");

    raise(SIGHUP);
    raise(SIGINT);
    raise(SIGQUIT);
    __asm__ volatile("int3");  // SIGTRAP
    // abort();  // SIGABRT
    // int *ptr = NULL;
    // *ptr = 7;  // SIGSEGV
    int zero = 0;
    printf("%d\n", 1 / zero);  // SIGFPE
    raise(SIGUSR1);
    raise(SIGUSR2);
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }
    close(fd[1]);
    read(fd[0], NULL, 1);  // SIGPIPE
    alarm(2);  // SIGALRM
    kill(getpid(), SIGTERM);
    raise(SIGSTKFLT);
    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    } else if (child_pid == 0) {
        // Child process
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;
        waitpid(child_pid, &status, 0);  // SIGCHLD
    }
    kill(getpid(), SIGSTOP);
    raise(SIGTSTP);
    pause();  // SIGCONT
    raise(SIGURG);
    // SIGXCPU and SIGXFSZ cannot be easily triggered in a small program
    struct itimerval timer;
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("setitimer");
        return EXIT_FAILURE;
    }
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("setitimer");
        return EXIT_FAILURE;
    }

    printf("Done.\n");

    return EXIT_SUCCESS;
}
