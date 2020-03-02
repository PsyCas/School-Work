Assignment 2 - Program 3

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Add Orientation to the Labeled Image
====================================================================================================================

1)  In this folder, there are files that solve the second Program of Assignment 2.
    The files contained are described below,

    a) image.h and image.cc: Files that will create a class representation for an input image.
    b) two_objectsLabeled.pgm | many_objects_1Labeled.pgm | many_objects_2Labeled.pgm: Output labeled images from p2.cc.
    c) p3.cc :  Solution for Problem 3.
                File that takes a labeled image, a database text file name and populated the text file with,
                    Object label, row position of the center, column position of the center, the minimum moment of inertia and the orientation
                as well as, outputs a new image plotting a line of length 35 from the center of the object with angle (theta) to the vertical axis.
    d) ./Results:   Contains the results I obtained from this program. 
    e) two_objectsOrientation.pgm | many_objects_1Orientation.pgm | many_objects_2Orientation.pgm: Output images from p3.cc containing a line drawn to show orientation.
    f) database_two_objects.txt | databaseMany1.txt | databaseMany2.txt: Text Database outputs from p3.cc. Contains information stated in (i) separated by spaces. 
    g) Makefile		: 	Makefile modified for this part of the assignment.

---------------------

2) To compile all files, type
	
	make clean
	make all

   To delete all .o files and .exe files, type

	make clean
----------------------

3)  Program 3
   =========
   Instructions to run Program 3 after compilation,
	
	./p3 <input labeled image> <output database name> <output file name>

	where,
		* input image is a labeled image.
		* output database name is a .txt file where the calculations will be saved for each identified object.
		* output file name is the name of the file where the image with orientation will be saved. 

	For example, you can type
		
		./p3 two_objectsLabeled.pgm databaseTwoObjects.txt two_objectsOrientation.pgm
		
		* This will add orientation to the image "two_objectsLabeld.pgm" and save it as "two_objectsLabeled.pgm".
        * It will also create a text file "databaseTwoObjects.txt" that contains teh database for this file.
----------------------

4) Input Files and Output Files given,

   For input and output files, reference pgm images and .txt databases in Part 1 of this document.

----------------------