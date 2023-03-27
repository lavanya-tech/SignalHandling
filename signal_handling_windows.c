#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <signal.h>
#include <wincon.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
// #define	SIGINT		2	/* Interactive attention */
// #define	SIGILL		4	/* Illegal instruction */
// #define	SIGFPE		8	/* Floating point error */
// #define	SIGSEGV		11	/* Segmentation violation */
// #define	SIGTERM		15	/* Termination request */
// #define SIGBREAK	21	/* Control-break */
// #define	SIGABRT		22	/* Abnormal termination (abort) */

// #define NSIG 23     /* maximum signal number + 1 */

void signal_handler(int signum) {
    printf("Received signal: %d\n", signum);
}

int main() {
    int ch;
    scanf("%d",&ch);
    signal(SIGINT,signal_handler);
    signal(SIGABRT,signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGFPE,signal_handler);
    signal(SIGSEGV,signal_handler);
    signal(SIGILL,signal_handler);
    signal(SIGBREAK,signal_handler);
    switch (ch)
    {
    case 1:{// SIGINIT
        while(1)
        {
            printf("In loop");
        }
        break;
    }
    case 2:{//SIGSEGV
        int *ptr = NULL;
        *ptr = 8;
        break;
    }
    case 3:{
        int zero = 0;
        printf("%d\n", 1 / zero);  // SIGFPE
        break;
    }
    case 4:{//SIGABRT
        abort();
        break;
    }
    case 5:{//SIGILL
        __asm__("ud2");
        break;
    }
    case 6:{
        GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, 0);
        break;
    }
    default:
        break;
    }
}