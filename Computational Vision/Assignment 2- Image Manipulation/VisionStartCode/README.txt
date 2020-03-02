Assignment 2

Written by  :  Parakram Basnet
Instructor  :  Ioannis Stamos
Class	      :  Computational Vision 

====================================================================================================================

1) In this folder, there are files that four problems of Assignment 2.
   The files and folders contained are described below,

   a) image.h and image.cc: Files that will create a class representation for an input image.
   
   b) two_objects.pgm | many_objects_1.pgm | many_objects_2.pgm: Provided sample test images.

   c) p1.cc :  Solution for Problem 1.
               File that takes a greyscale image, a greyscale threshold and an output file name. Then it converts
               the input file to binary image and saves it as the output file name.
   
   d) two_objectsBinary.pgm | many_objects_1Binary.pgm | many_objects_2Binary.pgm: Output images from p1.cc with threshold value 120. 
   
   e) ./Program 1: Folder containing the necessary files to run Program 1 (p1.cc).
                   Contains its own Makefile and instructions in README.txt.

   f) p2.cc :  Solution for Problem 2.
               File that takes a binary image and outputs a labeled image where every detected object has a separate label.

   g) two_objectsLabeled.pgm | many_objects_1Labeled.pgm | many_objects_2Labeled.pgm: Output labeled images from p2.cc.

   h) ./Program 2: Folder containing the necessary files to run Program 2 (p2.cc).
                   Contains its own Makefile and instructions in README.txt.

   i) p3.cc :  Solution for Problem 3.
               File that takes a labeled image, a database text file name and populated the text file with,
                  Object label, row position of the center, column position of the center, the minimum moment of inertia and the orientation
               as well as, outputs a new image plotting a line of length 35 from the center of the object with angle (theta) to the vertical axis.

   j) two_objectsOrientation.pgm | many_objects_1Orientation.pgm | many_objects_2Orientation.pgm: Output images from p3.cc containing a line drawn to show orientation.

   k) database_two_objects.txt | databaseMany1.txt | databaseMany2.txt: Text Database outputs from p3.cc. Contains information stated in (i) separated by spaces. 

   l) ./Program 3: Folder containing the necessary files to run Program 3 (p3.cc).
                   Contains its own Makefile and instructions in README.txt.

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
   
   n) many_objects_1RecognitionPt4.pgm | many_objects_2RecognitionPt4.pgm: Output images from p4.cc.

   o) ./Program 4: Folder containing the necessary files to run Program 3 (p3.cc).
                   Contains its own Makefile and instructions in README.txt.

   p) Makefile: Makefile modified for compiling all four programs.

---------------------

2) To compile all files, type
	
	make clean
	make all

   To delete all .o files and .exe files, type

	make clean

----------------------

3) Program 1
   =========
   Instructions to run Program 1 after compilation,
	
	./p1 <input file name> <grey-threshold value> <output file name>

	where,
		* input file is the greyscale image to convert to binary.
		* grey-threshold value is a value between 0 - 255 which is the threshold to convert the image.
		* output file name is the name of the file where the binary image will be saved. 
	
	For example, you can type
		
		./p1 objects.pgm 127 outputObjects.pgm
		
		* This will convert the image "objects.pgm" to a binary image using threshold value 127 and save it as "outputObjects.pgm" 	 

   Program 2
   =========
   Instructions to run Program 2 after compilation,
	
	./p2 <input binary image> <output file name>

	where,
		* input binary image is a binary image.
		* output file name is the name of the file where the labeled image will be saved. 

	For example, you can type
		
		./p2 two_objectsBinary.pgm two_objectsLabeled.pgm
		
		* This will convert the image "two_objectsBinary.pgm" from a binary image to a labeled image and save it as "two_objectsLabeled.pgm" 	 

   Program 3
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

   Program 4
   =========
   Instructions to run Program 4 after compilation,
	
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