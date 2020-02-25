Assignment 2 - Program 1

Written by:  Parakram Basnet
Instructor:  Ioannis Stamos
Class	  :  Computational Vision 

Convert Grayscale Image to Binary Image
====================================================================================================================

1) In this folder, there are files that solve the first Program of Assignment 2.
	
	a) image.h and image.cc :	Files that will create a class representation for an input image.
	b) p1.cc		: 	File that takes a greyscale image, a greyscale threshold and an output file name. Then it converts
					the input file to binary image and saves it as the output file name.
	c) Makefile		: 	Makefile modified for this part of the assignment.	

2) To compile all files, type
	
	make clean
	make all

   To delete all .o files and .exe files, type

	make clean

3) Instructions to run Program 1 after compilation,
	
	./p1 <input file name> <grey-threshold value> <output file name>

	where,
		* input file is the greyscale image to convert to binary.
		* grey-threshold value is a value between 0 - 255 which is the threshold to convert the image.
		* output file name is the name of the file where the binary image will be saved. 
	
	For example, you can type
		
		./p1 objects.pgm 127 outputObjects.pgm
		
		* This will convert the image "objects.pgm" to a binary image using threshold value 127 and save it as "outputObjects.pgm" 	 

4) Input Files and Output Files given,

	Input 	:	There are three input examples in this folder, "objects.pgm", "many_objects_1.pgm" and "many_objects_2.pgm".
	Output	:	There are three outputs in the Results folder. They are, "objectsBinary.pgm", "many_objects_1Binary.pgm" and "many_objects_2Binary.pgm".
			* All the output files are generated with the threshold 127.