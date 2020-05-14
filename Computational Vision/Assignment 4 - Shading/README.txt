Assignment 4

Written by  :  Parakram Basnet
Instructor  :  Ioannis Stamos
Class	      :  Computational Vision 

====================================================================================================================

1) In this folder, there are files for the four problems of Assignment 4.
   The files and folders contained are described below,

  a) image.h and image.cc: Files that will create a class representation for an input image.
  b) binaryImages.h and binaryImages.cc: Files that create a class representation for a binary image.

  c) sphere0.pgm | sphere1.pgm | sphere2.pgm | sphere3.pgm: Provided sample test images.
  d) object0.pgm | object1.pgm | object2.pgm | object3.pgm: Provided sample test images.
  e) needle.pgm  | albedo.pgm : Provide outputs for needle image and albedo.

  ********** Part 1 ***********  

  f) s1.cc :  Solution for Problem 1.
              File that takes a greyscale image, a threshold value and an output parameters file name. 
              Then, it locates the sphere in an image and computes its center and radius.
              THRESHOLD: 100

  g) sphere0_part1.txt : Output file for s1.cc. 
   
  ******************************
  *********** Part 2 ***********

  h) s2.cc :  Solution for Problem 2.
              File that takes the input parameters file from part 1, the three images and an output directions file.
              Computes the directions and intensities of the light sources and saves it in output directions file. 

  i) sphere0_part2.txt: Output file from s2.cc. 
   
  ******************************
  *********** Part 3 ***********

  j) s3.cc :  Solution for Problem 3.
              File that takes input directions file from part2, three images, a step value, threshold and output needle image.
              Computes the surface normals using three different images with different light sources. Creates a needle map to display the image.
              STEP: 15
              THRESHOLD: 85 

  k) sphere_needle.pgm: Output image from s3.cc. 
  
  ******************************
  *********** Part 4 ***********
  
   l) h4.cc :  Solution for Problem 4.
               File that takes input directions file from part2, three images, threshold and output albedo image.
               Computes the surface albedo and saves it as the output image file. 
               THRESHOLD USED: 85

   m) sphere_albedo.pgm: Output image from s4.cc. 
  
  ******************************

   n) matrixOperations.cc: File containing all necessary matrix operations.
   o) Makefile: Makefile modified for compiling all four programs.

---------------------

2) To compile all files, type
	
	make clean
	make all

  To compile one of the four parts, you can type

  make part1
  make part2
  make part3
  make part4

  To delete all .o files and .exe files, type

	make clean

----------------------

3) Program 1
   =========
   Instructions to run Program 1 after compilation,
	
	./s1 {input original image} {input threshold value} {output parameters file}

   Program 2
   =========
   Instructions to run Program 2 after compilation,
	
	./s2 {input parameters file} {image 1} {image 2} {image 3} {output directions file}

   Program 3
   =========
   Instructions to run Program 3 after compilation,
	
	./s3 {input directions} {image 1} {image 2} {image 3} {step} {threshold} {output}

   Program 4
   =========
   Instructions to run Program 4 after compilation,
	
	./s4 {input directions} {image 1} {image 2} {image 3} {threshold} {output}
----------------------

4) Input Files and Output Files given,

   For input and output files, reference pgm images and .txt databases in Part 1 of this document.

----------------------