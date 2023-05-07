#include <stdio.h>
#include <fcntl.h>    // file control options
#include <unistd.h>   // unix std lib
//#include <sys/stat.h> 

#define BYTE_TARGET 4

/**
 * @brief Copies content of `input.txt` to `output.txt`, then appends the content of `input.txt` from the BYTE_TARGET-th byte onwards.
 * 
 * @return int 
 */
int main() {
    int fd_in, fd_out;
    char str[100];

    // open file in READ mode
    fd_in = open("input.txt", O_RDONLY, 0);

    // open file in READ/WRITE/CREATE mode
    fd_out = open("output.txt", O_CREAT | O_RDWR, 0666);

    // write data from input to output
    ssize_t n;
    while ( (n = read(fd_in, str, 10)) > 0 )
        write(fd_out, str, n);

    // shift to BYTE_TARGET
    lseek(fd_in, BYTE_TARGET, SEEK_SET);
    
    // write to output again
    write(fd_out, "\n", 1);
    while ( (n = read(fd_in, str, 10)) > 0 )
        write(fd_out, str, n);
    
    // closing of files
    close(fd_in);
    close(fd_out);
    return 0;
}