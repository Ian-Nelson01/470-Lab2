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

    // this might actually make 1024 processes, but only ten are used.
    for (int i = 0; i < numChildren; i++){ // loop will run n times

        // fork into children at this point.
        pid = fork();
        if (pid == 0){ // this is ONLY the 0's.


            // switch statement aint working now something about exec's interfering with "break", 
            // even though i could use exec's in a switch yesterday.
            //i dont wanna think of a clever solution cuz im mad, it worked fine earlier.
            // goin yandev quality for a sec here.
            if( i == 0){
                // 1. print echo of phrase from lab
                printf("Child %d from parent %d uses the ECO command, \n", getpid(), getppid());
                const char* args[] = {"echo", "Hello Ian", NULL};
                if (execvp("echo", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }
            else if (i == 1){
                      // 2. List exec command
                printf("Child %d from parent %d uses the LS command, \n", getpid(), getppid());
                const char* args[] = {"ls", NULL};
                if (execvp("ls", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }
            else if (i == 2){
                      // 2. Date exec command
                printf("Child %d from parent %d uses the DATE command, \n", getpid(), getppid());
                const char* args[] = {"date", NULL};
                if (execvp("date", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }           
            else if (i == 3){
                      // 2. List username command
                printf("Child %d from parent %d uses the whoami command, \n", getpid(), getppid());
                const char* args[] = {"whoami", NULL};
                if (execvp("whoami", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }
            else if (i == 4){
                      // 5. List process
                printf("Child %d from parent %d uses the ps command, \n", getpid(), getppid());
                const char* args[] = {"ps", NULL};
                if (execvp("ps", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }            
            else if (i == 5){
                      // 6. // 6. print current working dir
                printf("Child %d from parent %d uses the pwd command, \n", getpid(), getppid());
                const char* args[] = {"pwd", NULL};
                if (execvp("pwd", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }            
            else if (i == 6){
                      // 6. // 7. print current file
                printf("Child %d from parent %d uses the cat command, \n", getpid(), getppid());
                const char* args[] = {"cat", "lab2.c",  NULL};
                if (execvp("cat", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }  
            else if (i == 7){          
                      // 8 ping a website
                printf("Child %d from parent %d uses the PING command, \n", getpid(), getppid());
                const char* args[] = {"ping", "https://github.com/Ian-Nelson01",  NULL};
                if (execvp("ping", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }  
            else if (i == 8){          
                      // 9 ping a website
                printf("Child %d from parent %d uses the mkdir command, \n", getpid(), getppid());
                const char* args[] = {"mkdir", "homework",  NULL};
                if (execvp("mkdir", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            }  
            else if (i == 9){          
                      // 10 touch process
                printf("Child %d from parent %d uses the touch command, \n", getpid(), getppid());
                const char* args[] = {"touch", "touch.txt",  NULL};
                if (execvp("touch", (char* const*)args) == -1){
                    perror("exec failed");
                    exit(1);
                }
            } 
            else{ 
                printf("default case hit somehow, check ya fork logic");
                _exit(99);
            }
        }
        
        if (pid < 0){
            printf("something went wrong with the fork statement");
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