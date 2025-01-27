#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "libmemdrv.h"
#include "fs.h"

#define BLOCK_SIZE 64
#define MAX_BID 78
#define TRUE 1

// the free list should be initialised with values 0 to MAX_BID - 1
static int8_t free_list[MAX_BID];
static char buf[BLOCK_SIZE] = {0};

// use this code to shuffle the storage position of data blocks
void shuffle(int8_t *array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int8_t t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

// when given the -r option, instead of storing data at
// sequential blocks (1,2,3... MAX_BID-1) data should be
// stored at positions determined by the values in free_list
// at positions (1,2,3... MAX_BID-1)

// initialize free list with the 0th position being unused
void init_free_list()
{
    for (int i = 0; i < MAX_BID; i++)
    {
        free_list[i] = 0;
    }
}

// searches through free list to find the first free block index
int find_free_block()
{
    for (int i = 0; i < MAX_BID; i++)
    {
        if (free_list[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    // Check for correct number of arguments
    if (argc < 2)
    {
        printf("Usage: store <filename> <file>\n");
        exit(0);
    }

    // opening of the file.
    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd < 0)
    {
        perror("open");
        exit(0);
    }

    // find the size of the input file using fseek this find the end position in the file and then
    // uses ftell to find the size of the file using the final position of feseek

    off_t file_size = lseek(input_fd, 0, SEEK_END);
    lseek(input_fd, 0, SEEK_SET);

    // checks to see if the file size is greater than the max block size
    if (file_size > BLOCK_SIZE * MAX_BID)
    {
        fprintf(stderr, "truncated\n");
        // If true then truncate the file size to the max block size
    }

    // check for randomise option
    if (argc == 3 && strcmp(argv[2], "-r") == 0)
    {
        shuffle(free_list + 1, MAX_BID - 1);
    }

    // Open the memdrv device
    open_device();

    while (TRUE)
    {
        // Read a block from the input file
        int bytes = read(input_fd, buf, BLOCK_SIZE);

        // If there are bytes (bytes>0), then loop BLOCKSIZE, if bytes==0 then break
        if (bytes > 0)
        {
            for (int i = 0; i < BLOCK_SIZE; i++)
            {

                // Find a free block
                int block = find_free_block();

                if (block == -1)
                {
                    fprintf(stderr, "no space\n");
                    break;
                }

                // Write the block to the memdrv device
                write_block(block, buf);
                free_list[block] = 1;
            }
        }
        else
        {
            printf("File stored\n");
            break;
        }
    }
    // Close the memdrv device
    close_device();

    // Close the input file
    close(input_fd);
}