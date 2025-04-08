#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global = 0;

int main(int argc, char *argv[]) {
    int local = 0;
    
    if(argc != 2) {
        fprintf(stderr, "Błąd przy podawaniu argumentu");
        exit(EXIT_FAILURE);
    }

    printf("Nazwa: %s\n", argv[0]);
    
    pid_t child_pid = fork();
    if(child_pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if(child_pid == 0) {
        printf("child process\n");
 
        global++;
        local++;
        
        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
        printf("child's local = %d, child's global = %d\n", local, global);
   
        int ret = execl("/bin/ls", "ls", argv[1], (char *)NULL);
        perror("execl failed");
        exit(ret);
    } else { 
        int status;
        if(wait(&status) < 0) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        
        printf("parent process\n");
        printf("parent pid = %d, child pid = %d\n", getpid(), child_pid);
        
        if(WIFEXITED(status)) {
            printf("Child exit code: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child did not exit normally.\n");
        }
        
        printf("Parent's local = %d, parent's global = %d\n", local, global);
        
        exit(EXIT_SUCCESS);
    }
}
