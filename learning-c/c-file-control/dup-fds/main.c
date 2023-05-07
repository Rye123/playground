#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define N 50

/**
 * @brief Reads up to the N-th character, then uses a different file descriptor to read until EOF
 * 
 * @return int 
 */
int main() {
    int fd_in1, fd_in2;
    ssize_t n;
    char buffer[1];
    int counter = 0;

    // initialise fds
    fd_in1 = open("input.txt", O_RDONLY, 0); // fd4
    fd_in2 = dup(fd_in1);                    // fd5

    while ( (n = read(fd_in1, buffer, 1)) > 0 ) {
        printf("%c", buffer[0]);
        counter ++;
        if (counter >= N)
            break;
    }

    printf("\nReading from fd_in2.\n");
    while ( (n = read(fd_in2, buffer, 1)) > 0 ) {
        printf("%c", buffer[0]);
    }

    return 0;
}