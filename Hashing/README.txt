Assignment 3: Hashing
Written by: Parakram Basnet
Instructor: Ioannis Stamos
Class:      CSCI 335

1) Parts of the assignment that were completed:

    a) Part 1   
    b) Part 2 
    c) Part 3a 
    d) Part 3b
    e) Part 3c

    Incomplete Parts: None

    NOTES*: 
        1) The values for Collision is about 150-200 less than "expected output" on Cygwin g++ 7.3.0.
        2) The values for number of probes for some words are not the same as "expected output" but "Found" and "Not Found" are correct.

2)  To compile all files, type

        make clean
        make all

    To compile program individually, type make <Program Name>. For example,

        make create_and_test_hash

    To delete all .o files and executables, type

        make clean

3) Instructions for running individual parts,

    a)  To run part 1 and 2, compile all files and type,

            ./create_and_test_hash <words file name> <query words file name> <flag>

            where,
                * words file contains words to store in hash table
                * query words file containts words to search for in the hash table
                * flag is the type of probing to use. Accepted values are "linear", "quadratic" or "double" 

        For example, you can also type

            ./create_and_test_hash words.txt query_words.txt double

    b)  To run part 3, compile all files and type,

            spell_check <document file> <dictionary file>

            where,
                * document file contains the file to spell check
                * dictionary file contains the dictionary
        
        For these set of files, you can type
            ./spell_check document1.txt wordsEn.txt
            
4) This program has two input files for part 1 and 2,

        words.txt    <- file containing words to enter into a hash table.
        query_words.txt   <- file containing words to search for in the hash table.

    For part 3, it has three input files, of which only two document files can be used alternatively,

        wordsEn.txt    <- dictionary file
        document1.txt  <- larger sample document containing misspelled words 
        document1_short.txt  <- smaller sample document containing misspelled words 