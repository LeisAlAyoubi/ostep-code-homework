#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // 1.
        // execl("/bin/ls", "ls", "-l", "-a", NULL);

        // 2.
        // char *envp[] = {"HOME=/usr/home", "LOGNAME=home", NULL};
        // execle("/bin/ls", "ls", "-l", NULL, envp);
        // printf("this shouldn't print out");

        // 3.
        // execlp("ls", "ls", "-l", NULL);

        // 4.
        // char *args[] = {"ls", "-l", "-a", NULL};
        // execv("/bin/ls", args);

        // 5.
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);

        // 6.
        // char *args[] = {"ls", "-l", NULL};
        // char *envp[] = {"HOME=/usr/home", "LOGNAME=home", NULL};
        // execvpe("ls", args, envp);
    }
    else
    {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        assert(wc >= 0);
    }
    return 0;
}
