#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// 6.
// Write a slight modification of the previous program, this time using
// waitpid() instead of wait().When would waitpid() be useful ?

int main(int argc, char *argv[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        sleep(1);
    }
    else
    {
        // Parent process
        int status;
        pid_t waited_pid = waitpid(pid, &status, 0);

        if (waited_pid == -1)
        {
            perror("waitpid failed");
            return 1;
        }

        // Check if the child exited normally
        if (WIFEXITED(status))
        {
            printf("Child process %d exited with status %d\n", waited_pid, WEXITSTATUS(status));
        }
        else
        {
            printf("Child process %d did not exit normally\n", waited_pid);
        }
    }
    return 0;
}
