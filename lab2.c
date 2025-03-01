#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define NUM_COMMANDS 10

int main()
{
    // establish pid so it can be in scope outside the loop
    pid_t pid;
    int numChildren = 10; // 10;

    // set up an array to hold commands,
    // switch statement in my old version mysteriously stopped working
    const char *command[NUM_COMMANDS][3] = {

        // command grid is a more space effective way to do things.
        {"echo", "Hello Ian", NULL},                      // 1. print echo of phrase from lab
        {"ls", NULL},                                     // 2. List exec command
        {"date", NULL},                                   // 3. Date exec command
        {"whoami", NULL},                                 // 4. List username command
        {"ps", NULL},                                     // 5. List process
        {"pwd", NULL},                                    // 6. print current working dir
        {"cat", "lab2.c", NULL},                          // 7. print current file
        {"mkdir", "homework", NULL},                      // 8 make a dir
        {"touch", "touch.txt", NULL},                     // 9 make a file
        {"ping", "https://github.com/Ian-Nelson01", NULL} // 10 ping a website
    };

    // this might actually make 1024 processes, but only ten are used.
    for (int i = 0; i < numChildren; i++)
    { // loop will run n times

        // fork into children at this point.
        pid_t pid = fork();
        if (pid == 0)
        {
            // display message and run exec statement based off the command grid
            printf("Child %d from parent %d uses the %s command!, \n", getpid(), getppid(), command[i][0]);
            if (execvp(command[i][0], (char *const *)command[i]) == -1)
            {
                perror("exec failed");
                exit(1);
            }
        }
    } // end of the loop

    // wait for stuff to finish and report status
    for (int i = 0; i < numChildren; i++)
    {
        int status;
        pid_t child_pid = waitpid(-1, &status, 0); // wait for any child

        if (child_pid > 0)
        { // validate child process has exited
            if (WIFEXITED(status))
            {
                printf("Child %d exited with status: %d\n", child_pid, WEXITSTATUS(status));
            }
            else if (WIFSIGNALED(status))
            {
                printf("Child %d was killed by a signal\n", child_pid);
            }
            else
            {
                printf("Child %d exited abnormally\n", child_pid);
            }
        }
    }
    return (0);
}
