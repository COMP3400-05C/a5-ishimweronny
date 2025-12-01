#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Main function to count the number of letters in each category in a file
 * @param argc Number of arguments
 * @param argv Arguments
 * @return Exit status
 */
int main(int argc, char* argv[]) {
    // Show usage if no arguments are provided
    if (argc != 2) {
        printf("USAGE: parta FILEIN\n");
        return 1;
    }

    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];
    
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("ERROR: %s not found\n", argv[1]);
        return 2;
    }

    int read_bytes;

    // Count the number of letters in each category
    int upper_count = 0;
    int lower_count = 0;
    int number_count = 0;
    int space_count = 0;
    int other_count = 0;
    
    while ((read_bytes = read(fd, buffer, BUFSIZE)) > 0) {
        for (int i = 0; i < read_bytes; i++) {
            if (isupper(buffer[i])) {
                upper_count++;
            } else if (islower(buffer[i])) {
                lower_count++;
            } else if (isdigit(buffer[i])) {
                number_count++;
            } else if (isspace(buffer[i])) {
                space_count++;
            } else {
                other_count++;
            }
        }
    }

    printf("Upper,%d\n", upper_count);
    printf("Lower,%d\n", lower_count);
    printf("Number,%d\n", number_count);
    printf("Space,%d\n", space_count);
    printf("Other,%d\n", other_count);

    close(fd);

    return 0;
}
