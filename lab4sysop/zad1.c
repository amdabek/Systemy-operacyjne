#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Błąd przy wpisywaniu argumentów");
        exit(EXIT_FAILURE);
    }
    
    int num = atoi(argv[1]);
    if(num <= 0) {
        fprintf(stderr, "Liczba ma być dodatnia\n");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid;
    for (int i = 0; i < num; i++) {
        pid = fork();
        if(pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if(pid == 0) { 
            printf("Parent PID: %d, Child PID: %d\n", getppid(), getpid());
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < num; i++) {
        wait(NULL);
    }

    printf("%s\n", argv[1]);
    
    return 0;
}
