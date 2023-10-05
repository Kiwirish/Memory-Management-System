#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libmemdrv.h"
#include "fs.h"

#define INODE_BLOCK 0

int main(int argc, char *argv[]){

    Inode inode; 
    char buf[BLOCK_SIZE];
    // char *outputFilename = NULL; 
    //FILE *output = stdout; 

    // the retrieve program only expects 2  input arguments at command line
    // If theres 


}

// open the /dev/memdrv device 
open_device();

// Direct block of data retrieval using iNodes direct addresses 
for (int i = 0 ; i < NDIRECT ; i++){
    if (inode.addrs[i]){
        read_block(inode.addrs[i], buf);
        //fwrite(buf, sizeof(char), BLOCK_SIZE, outfile);
    }
}

// this is only the last inode index
// Indirect blocks of data retrieval 
// The file data exceeds storage in the direct blocks if the inode has an indirect address
if(inode.addrs[NDIRECT]){
    // indirect block 
    int8t_t indirect[BLOCK_SIZE];
    read_block(inode.addrs[NDIRECT], (char*)indirect);

    // if the indirect block is full, retrieve it all by looping over 
    for(int i = 0; i < BLOCK_SIZE ; i++){
        if(indirect[i]){
            read_block(indirect[i], buf);
            //fwrite(buf, sizeof(char), BLOCK_SIZE, outfile);
        }
    }
}
// close the device 
close_device();

if (output)
