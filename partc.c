#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // check for args
    if (argc != 2) {
        fprintf(stderr, "USAGE: partc FILEIN\n");
        exit(1);
    }
    
    char *input_filename = argv[1];
    
    // create pipe
    int pipe_fds[2];
    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        exit(1);
    }
    
    int pipe_read_fd = pipe_fds[0];
    int pipe_write_fd = pipe_fds[1];
    
    // create child
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    
    if (pid > 0) {
        // close read end on parent
        close(pipe_read_fd);
        
        // redirect STDOUT to pipe end
        dup2(pipe_write_fd, STDOUT_FILENO);
        close(pipe_write_fd);
        
        // use parta with filename
        char *parta_args[] = {"./parta", input_filename, NULL};
        execv("./parta", parta_args);
        
        // check error
        perror("execv parta");
        exit(1);
    } else {
        // close write end of child
        close(pipe_write_fd);
        
        // redirect STDIN to pipe read end
        dup2(pipe_read_fd, STDIN_FILENO);
        close(pipe_read_fd);
        
        // sort
        char *sort_args[] = {"sort", "-t,", "-k2", "-n", NULL};
        execvp("sort", sort_args);
        
        perror("execvp sort");
        exit(1);
    }
    
    return 0;
}
