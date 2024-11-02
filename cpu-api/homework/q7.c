#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

// 7. Write a program that creates a child process, and then in the child closes standardoutput(STDOUT FILENO).
// What happens if the child calls printf() to print some output after closing the descriptor?

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
        close(STDOUT_FILENO);
        // // New output file before fork()
        // open("./q2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        sleep(1);
    }
    else
    {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        assert(wc >= 0);
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int)getpid());
    }
    return 0;
}
