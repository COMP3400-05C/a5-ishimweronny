#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 * Main function to execute the parta program and redirect the output to a file
 * @param argc Number of arguments
 * @param argv Arguments
 * @return Exit status
 */
int main(int argc, char* argv[]) {
    // show usage if no arguments are provided
    if (argc != 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    // open the file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("ERROR: %s not found\n", argv[1]);
        return 2;
    }

    // open the output file
    int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0770);
    if (fd_out == -1) {
        printf("ERROR: %s not found\n", argv[2]);
        return 3;
    }

    // redirect STDOUT to the output file
    if (dup2(fd_out, STDOUT_FILENO) == -1) {
        perror("dup2"); // error checking
        return 3;
    }
    close(fd_out);

    // write header line
    if (dprintf(STDOUT_FILENO, "Category,Count\n") < 0) {
        perror("write header"); // error checking
        return 3;
    }

    // exec the parta program (argv[0] set to "parta")
    if (execl("./parta", "parta", argv[1], (char*)NULL) == -1) {
        perror("exec parta"); // error checking
        return 4;
    }

    return 4;
}
