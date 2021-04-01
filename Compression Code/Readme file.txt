About Huffman Coding:-

a) The Huffman Coding is required when there is a need of lossless data compression. This method uses a unique way by assigning each character present in the input file a 
   unique binary code.

b) The binary codes assigned to characters follows something known as prefix code. This means that each and every binary code assigned to a character will have a unique 
   prefix from which it can be differentiated from others.

c) Now to assign binary codes, the first step required is to form a huffman tree which is formed on the basis of number of different character present in the input file 
   and their respective frequencies. 

d) After the codes are assigned, all the characters in the input file are then replaced with their respective binary code and stored in a binary file(.dat).

e) Since the assigned code is always of length less than a byte (i.e. less than 8 characters), replacing each character with their binary code performs compression. 

f) Next then to perform decompression, it reads bit by bit at a time from binary file and compares it with the assign binary code values. If a match is found then it 
   prints the character associated with that binary code in an output file otherwise it reads the next bit concatenate both bits and again look for match. This process
   is repeated until the end of the file.

How to use the code:-

I) For Compression:

a) First open the file named as "Huffman encode.cpp". This file contains the compression code. At starting, a file will be taken as input on which compression will be 
   performed. Thus, make sure that the input file and the compression code file are together in the same folder otherwise an error will be displayed.
b) After running the code, a compressed file with extension .dat will be formed.
c) The name of input file is of format "Huffman Code Test_file_N.txt" while that of the compressed file is of "Encoded file_N.dat", where "N" stands for file number.

II) For decompression:

a) First open the file named as "Huffman decode.cpp". This file contains the decompression code. At starting the input file on which compression was required to be 
   performed will be taken as input to form the huffman tree. Then later on the compressed file on which decompression is required to be performed will be taken as input. 
   Thus, make sure that the input file, decompression code file and the compressed file all are together in the same folder.
b) After running the code, a decompressed file with extension .txt will be formed.
c)The name of the decompressed file will be of format "Decoded file_N.txt" where "N" stands for file number.

Few test cases:-

Test case no.      Input file name           Input file size    Compressed file name    Compressed file size    Decompressed file name    Decompressed file size

   1.        Huffman Code Test_file_1.txt         57kb           Encoded file_1.dat            31kb               Decoded file_1.dat              57kb

   2.        Huffman Code Test_file_2.txt         17kb           Encoded file_2.dat             9kb               Encoded file_2.dat              17kb

Thus, here generally it is providing about 50% compression efficiency.

Note:-

a) While performing compression, the code stores the assigned binary values in a binary file. Now the size of assigned values is of less characters than standard 8 
   characters thus it is possible that the length of all the codes together in the binary file may not be of a multiple of 8. Thus, few zeroes may be added at the end
   of each compression to cope up with that. This can result in a few extra characters at the end of the decompressed file. However, it cannot be avoided.
b) The compressing efficiency of the code depends upon the number of different characters in the input file and their respective frequency. Thus, the compression ratio
   will vary from file to file.  