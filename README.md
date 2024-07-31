# Memory Management System (cosc204) :

# Retrieve program - 
#    5 Oct   
#   - MakeFile makes retrieve-prog from retrieve.c source file 
#   - Reads inode structure from block 0 
#   - Direct block retrieval without writing to output 
#   - Indirect block retrieval without writing to output yet 
#   - Must yet add argument handling 
#   - Must yet add output file / stdout stuff 

#   6 Oct 
#   - retrieve program handles arguments 
#   - retrieve program goes by current size of inode  
#   - retrieve program successfully retrieves the data the same as sample-retrieve

# 7 Oct
#   -added The store programto handle random argument
#   -Added the shuffle
#   -Needed to add freelist to keep track of unused blocks
#   -Need to properly add the truncate function

# 8 Oct
#   -Updated store to write block to memory using the freelist


