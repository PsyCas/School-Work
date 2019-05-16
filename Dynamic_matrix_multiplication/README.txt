Assignment 5: Find Optimal Order of Matrix Multiplications Using Dynamic Programming
Written by: Parakram Basnet
Instructor: Ioannis Stamos
Class:      CSCI 335

1) Parts of the assignment that were completed:

    a) Part 1   
    b) Extra Credit 

    Incomplete Parts: None
            
2)  To compile all files, type

        make clean
        make all

    To compile program individually, type make <Program Name>. For example,

        make optimal_multiplcations

    To delete all .o files and executables, type

        make clean

3) Instructions for running individual parts,

    a)  To run part, compile all files and type,

            ./optimal_multiplications <dimensions file name> 

            where,
                * dimensions file contains the dimensions of "n" number of matrices

        For example, to run the program with the given default file,

            ./optimal_multiplications dimensions_file.txt
            
4) This program has one input file containing an integer per line,

        dimensions_file.txt  <- Dimensions file containing the order of different matrices