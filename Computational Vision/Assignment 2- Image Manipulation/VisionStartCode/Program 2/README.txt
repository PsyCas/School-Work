Assignment 2 - Program 2

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Convert Binary Image to Labeled Image
====================================================================================================================

1)  In this folder, there are files that solve the second Program of Assignment 2.
    The files contained are described below,

    a) image.h and image.cc: Files that will create a class representation for an input image.
    b) two_objectsBinary.pgm | many_objects_1Binary.pgm | many_objects_2Binary.pgm: Output images from p1.cc with threshold value 120. 
    c) p2.cc:       Solution for Problem 2.
                    File that takes a binary image and outputs a labeled image where every detected object has a separate label.
    d) ./Results:   Contains the results I obtained from this program. 
    e) two_objectsLabeled.pgm | many_objects_1Labeled.pgm | many_objects_2Labeled.pgm: Output labeled images from p2.cc.
    f) Makefile		: 	Makefile modified for this part of the assignment.

---------------------
2) To compile all files, type
	
	make clean
	make all

   To delete all .o files and .exe files, type

	make clean

----------------------

3)  Instructions to run Program 2 after compilation,
	
	./p2 <input binary image> <output file name>

	where,
		* input binary image is a binary image.
		* output file name is the name of the file where the labeled image will be saved. 

	For example, you can type
		
		./p2 two_objectsBinary.pgm two_objectsLabeled.pgm
		
		* This will convert the image "two_objectsBinary.pgm" from a binary image to a labeled image and save it as "two_objectsLabeled.pgm" 	 
----------------------

4) Input Files and Output Files given,

   For input and output files, reference pgm images and .txt databases in Part 1 of this document.

----------------------