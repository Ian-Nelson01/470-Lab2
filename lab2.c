#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


//lab2.c

int main(){
    // establish pid so it can be in scope outside the loop
    pid_t pid;
    int numChildren = 10; // 10;
    
    // set up an array to hold commands, 
    //switch statement in my old version mysteriously stopped working
    const char* command[10];
    
    // command grid is a more space effective way to do things.
    command[0] = (const char*[]){"echo", "Hello Ian", NULL}; // 1. print echo of phrase from lab        
    command[1] = (const char*[]){"ls", NULL}; // 2. List exec command      
    command[2] = (const char*[]){"date", NULL}; // 3. Date exec command      
    command[3] = (const char*[]){"whoami", NULL}; //4. List username command
    command[4] = (const char*[]){"ps", NULL};// 5. List process      
    command[5] = (const char*[]){"pwd", NULL}; // 6. print current working dir       
    command[6] = (const char*[]){"cat", "lab2.c",  NULL}; // 7. print current file    
    command[7] = (const char*[]){"mkdir", "homework",  NULL}; // 8 make a dir     
    command[8] = (const char*[]){"touch", "touch.txt",  NULL}; // 9 make a file      
    command[9] = (const char*[]){"ping", "https://github.com/Ian-Nelson01",  NULL}; // 10 ping a website

    // this might actually make 1024 processes, but only ten are used.
    for (int i = 0; i < numChildren; i++){ // loop will run n times

        // fork into children at this point.
        pid = fork();
        // display message and run exec statement based off the command grid
        printf("Child %d from parent %d uses the %d command, \n", getpid(), getppid(), command[i][1]);
             if (execvp(command[i][1], command[i]) == -1){
             perror("exec failed");
             exit(1);
        }
    } // end of the loop

    // wait for stuff to finish and report status
    for (int i = 0; i < numChildren; i++){
        int status;
        pid_t child_pid = waitpid(-1, &status, 0); // wait for any child

        if (child_pid > 0){ // validate child process has exited
            if (WIFEXITED(status)){
                printf("Child %d exited with status: %d\n", child_pid, WEXITSTATUS(status));
            }else if (WIFSIGNALED(status)){
                printf("Child %d was killed by a signal\n", child_pid);
            }else{
                printf("Child %d exited abnormally\n", child_pid);
            }
        }
    }
    return (0);
}
