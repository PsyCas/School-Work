Assignment 2 - Program 4

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Recognize Images From Input Database
====================================================================================================================

1)  In this folder, there are files that solve the second Program of Assignment 2.
    The files contained are described below,

    a) image.h and image.cc: Files that will create a class representation for an input image.
    b) two_objectsLabeled.pgm | many_objects_1Labeled.pgm | many_objects_2Labeled.pgm: Output labeled images from p2.cc.
    m) p4.cc :  Solution for Problem 4.
                File that takes a labeled image, a populated database text file and outputs an image with the following changes,
               
                i.) Since these are different images, we cannot compare labels and centers. The database also does not contain the area, so we can-
                    -not use it either.
                ii.) Comparison is done through - 
                    if
                        0.88 <= ratio of moment < 1.12 and difference of degrees <= 10 will be considered similar --> color 255
                    else if 
                        0.88 <= ratio of moment < 1.12  but difference of degrees > 10, similar but different orientation --> color 127
                    else 
                        not similar --> color -> 25 
    d) ./Results:   Contains the results I obtained from this program. 
    n) many_objects_1RecognitionPt4.pgm | many_objects_2RecognitionPt4.pgm: Output images from p4.cc.
    f) database_two_objects.txt | databaseMany1.txt | databaseMany2.txt: Text Database outputs from p3.cc. Contains information stated in (i) separated by spaces. 
    g) Makefile		: 	Makefile modified for this part of the assignment.

---------------------

2) To compile all files, type
	
	make clean
	make all

   To delete all .o files and .exe files, type

	make clean
----------------------

4)  Instructions to run Program 4 after compilation,
	
	./p4 <input labeled image> <input database name> <output file name>

	where,
		* input image is a labeled image.
		* input database name is a .txt file where data from a different image will be imported from.
		* output file name is the name of the file where the recognized image will be saved. 

	For example, you can type
		
		./p4 many_objects_2Labeled.pgm databaseTwoObjects.txt many_objects_2RecognitionPt4.pgm
		
		* This will add orientation to the recognized objects in "many_objects_2Labeled.pgm" and save it as "many_objects_2RecognitionPt4.pgm".
----------------------

4) Input Files and Output Files given,

   For input and output files, reference pgm images and .txt databases in Part 1 of this document.

----------------------