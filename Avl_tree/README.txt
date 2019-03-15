Assignment 2
Written by: Parakram Basnet
Instructor: Ioannis Stamos
Class:      CSCI 335

1) Parts of the assignment that were completed:

    a) Part 1 (a, b, c ,d)
    b) Part 2a
    c) Part 2b (1, 2, 3a, 3b, 4a, 4b, 5a, 5b(slightly off), 6a, 6b(slightly off), 6c(slightly off))
    d) Part 2c

    Incomplete Parts: None

2)  To compile all files, type

        make clean
        make all

    To compile program individually, type make <Program Name>. For example,

        make query_tree

    To delete all .o files and executables, type

        make clean

3) Instructions for running individual parts,

    a)  To run part 2a, compile all files and type,

            ./query_tree rebase210.txt 

        and enter three recognition strings. Or, you can also type

            ./query_tree rebase210.txt < input_part2a.txt
    
        where   rebase210.txt is The Restriction Enzyme Database
                input_part2a.txt is a text file with three recognition sequences 

    b)  To run part 2b, compile all files and type,

            ./test_tree rebase210.txt sequences.txt

        where sequences.txt is a text file containing sample recognition sequences

    c)  To run part 2c, compile all files and type,

            ./test_tree_mod rebase210.txt sequences.txt

4) This program has one input and output file for part 2a,

        input_part2a.txt    <- file containing sample recognition sequences.
        output_part2a.txt   <- file containing expected output for the sequences in input_part2a.txt

    For part 2b, it had one output file,

        output_part2b.txt   <- file containing the expected output for 2b using data from rebase210.txt