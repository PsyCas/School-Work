Assignment 4: Graph Representation
Written by: Parakram Basnet
Instructor: Ioannis Stamos
Class:      CSCI 335

1) Parts of the assignment that were completed:

    a) Part 1   
    b) Part 2 
    c) Part 3 

    Incomplete Parts: None

    NOTES*: 
        1) For header file disjoint_sets.h, I had to add "#include disjoint_sets.cc" for it to work on Cygwin g++ 7.3.0. In case of any
        erros, please remove that line and proceed with compilation.
            
2)  To compile all files, type

        make clean
        make all

    To compile program individually, type make <Program Name>. For example,

        make CreateGraphAndTest
        make FindPaths
        make TestRandomGraph

    To delete all .o files and executables, type

        make clean

3) Instructions for running individual parts,

    a)  To run part 1, compile all files and type,

            ./CreateGraphAndTest <graph file name> <adjacency query file name>

            where,
                * graph file contains vertices, their adjacent vertices and their weight
                * adjacency query file containts queries to search for in the graph

        For example, you can also type

            ./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt

            *Note:
                1. The queries for Graph1 are stored in AdjacencyQueries1, Graph2 in AdjacencyQueries2 and so on.

    b)  To run part 2, compile all files and type,

            ./FindPaths <graph file> <Starting vertex>

            where,
                * graph file contains vertices, their adjacent vertices and their weight
                * Startin vertex is the vertex where the program will find the paths from
        
        For these set of files, you can type
            ./FindPaths graph2.txt 1

    b)  To run part 3, compile all files and type,

            ./TestRandomGraph <max number of nodes>

            where,
                * max number of nodes is the number of nodes in the graph
        
        For this program, you can type
            ./TestRandomGraph 20

            which creates a graph with 20 nodes.
            
4) This program has two input files for part 1 and 3 input files for part 2,

        Graph1.txt      <- graph file containing vertices, their adjacent vertices and their weight.
        AdjacencyQueries1 <- Containes vertices that are to queried for Graph1.txt.

        Graph2.txt      <- Another graph file containing vertices, their adjacent vertices and their weight.
        AdjacencyQueries2 <- Containes vertices that are to queried for Graph2.txt.

        Graph3.txt      <- Another graph file containing vertices, their adjacent vertices and their weight.