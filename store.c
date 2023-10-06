#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libmemdrv.h"
#include "fs.h"
#include "random.c"

#define BLOCK_SIZE 64
#define MAX_BID 78



int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc  < 2)
    {
        printf("Usage: store <filename> <file>\n");
        exit(0);
    }


    //opening of the file.
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd < 0)
    {
        perror("open");
        exit(0);
    }

    //find the size of the input file using fseek this find the end position in the file and then
    //uses ftell to find the size of the file using the final position of feseek

    off_t file_size = lseek(input_fd, 0, SEEK_END);
    lseek(input_fd, 0, SEEK_SET);

    //checks to see if the file size is greater than the max block size
    if (file_size > BLOCK_SIZE*MAX_BID)
    {
        fprintf(stderr, "truncated\n");
        file_size = BLOCK_SIZE * MAX_BID;
    }

    //create a file buffer.
    char *file_buffer = malloc(file_size);
    if (file_buffer == NULL)
    {
        perror("malloc");
        exit(0);
    }

    // Calculate the number of blocks needed
    int num_blocks = (file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // check for randomise option
    if (argc == 3 && strcmp(argv[2], "-r") == 0)
    {
       //shuffle(
    }
   

    // Open the memdrv device
    open_device();

    //write the file to the device
    int block_id = 0;
    char buf[BLOCK_SIZE];
    for(int i = 0; i < file_size; i += BLOCK_SIZE)
    {
        read(input_fd, buf, BLOCK_SIZE);
        write_block(block_id, buf);
        block_id++;
    }

    // Close the memdrv device
    close_device();

    // Close the input file
    close(input_fd);

}