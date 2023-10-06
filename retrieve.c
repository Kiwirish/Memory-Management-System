#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "libmemdrv.h"
#include "fs.h"

#define INODE_BLOCK 0


int main(int argc, char *argv[]){

    int fd = 1; 
    if (argc == 2){
        fd = open(argv[1], O_CREAT | O_WRONLY, 0644);
        if (fd == -1){
            perror("Open"); 
            return -1;
        }
    }

    Inode *inode = malloc(BLOCK_SIZE); 
    char buf[BLOCK_SIZE];
    char indirectBlock[BLOCK_SIZE]; 

    open_device(); 


    // read block 0  
    read_block(0, (char*)inode); 
    
    int size = (*inode).size;

    // direct block loop 
    for(int i =0 ; i < NDIRECT ; i++){

        read_block((*inode).addrs[i], buf);

        // if enough size, write to buf 
        if(size > BLOCK_SIZE){

            write(fd, buf, BLOCK_SIZE);
            size = size - BLOCK_SIZE;

        }else if(size == 0){
            break;
        }else{
            write(fd, buf , size);
            size = size - BLOCK_SIZE; 
            break; 
        }


    }

    // indirect block
    if(size > 0){

        read_block((*inode).addrs[NDIRECT], indirectBlock);

        for(int i =1 ; i < NDIRECT ; i++){

            read_block((int)indirectBlock[i], buf);

            // if enough size, write to buf 
            if(size > BLOCK_SIZE){

                write(fd, buf, BLOCK_SIZE);
                size = size - BLOCK_SIZE;

            }else if(size == 0){
                break;
            }else{
                write(fd, buf , size);
                size = size - BLOCK_SIZE; 
                break; 
            }
        }

    }
    
    close_device(); 

    free(inode);

    return EXIT_SUCCESS; 

}

/// freads reads from a file a block at ta time , and puts it straight into teh bufer. Good command for the store program. 

// open the /dev/memdrv device 
// open_device();

// read_block(1, inode); 

// int size = inode.size; 

// // Direct blocks 

// // if size is greater than block size read direct blocks 


// // Direct block of data retrieval using iNodes direct addresses 
// for (int i = 0 ; i < NDIRECT ; i++){
//     if (inode.addrs[i]){
//         read_block(inode.addrs[i], buf);
//         // append that buffer to a huge character array 
//         // char * File_out, keep wirin ot that. 
//         fwrite(buf, sizeof(char), BLOCK_SIZE, outputFile);
//         write()
//     }
// }



// // this is only the last inode index
// // Indirect blocks of data retrieval 
// // The file data exceeds storage in the direct blocks if the inode has an indirect address
// if(inode.addrs[NDIRECT]){
//     // indirect block array 
//     int8t_t indirect[BLOCK_SIZE];
//     // read  indirect inode addresses
//     read_block(inode.addrs[NDIRECT], (char*)indirect);

//     // if the indirect block is full, retrieve it all by looping over 
//     for(int i = 0; i < BLOCK_SIZE ; i++){
//         if(indirect[i]){
//             read_block(indirect[i], buf);
//             fwrite(buf, sizeof(char), BLOCK_SIZE, outfile);
//         }
//     }
// }
// // last block caclulation 

// // close the device 
// close_device();

// // output stuff 
// //if (output)
