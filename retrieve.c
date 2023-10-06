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
/// freads reads from a file a block at ta time , and puts it straight into teh bufer. Good command for the store program. 

// open the /dev/memdrv device 
open_device();

// Direct block of data retrieval using iNodes direct addresses 
for (int i = 0 ; i < NDIRECT ; i++){
    if (inode.addrs[i]){
        read_block(inode.addrs[i], buf);
        // append that buffer to a huge character array 
        // char * File_out, keep wirin ot that. 
        //fwrite(buf, sizeof(char), BLOCK_SIZE, outfile);
    }
}

// this is only the last inode index
// Indirect blocks of data retrieval 
// The file data exceeds storage in the direct blocks if the inode has an indirect address
if(inode.addrs[NDIRECT]){
    // indirect block array 
    int8t_t indirect[BLOCK_SIZE];
    // read  indirect inode addresses
    read_block(inode.addrs[NDIRECT], (char*)indirect);

    // if the indirect block is full, retrieve it all by looping over 
    for(int i = 0; i < BLOCK_SIZE ; i++){
        if(indirect[i]){
            read_block(indirect[i], buf);
            //fwrite(buf, sizeof(char), BLOCK_SIZE, outfile);
        }
    }
}
// last block caclulation 

// close the device 
close_device();

// output stuff 
//if (output)
