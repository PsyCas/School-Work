Assignment 3

Written by  :  Parakram Basnet
Instructor  :  Ioannis Stamos
Class	      :  Computational Vision 

====================================================================================================================

1) In this folder, there are files for the four problems of Assignment 3.
   The files and folders contained are described below,

  a) image.h and image.cc: Files that will create a class representation for an input image.
  
  b) hough_complex_1.pgm | hough_simple_1.pgm | hough_simple_2.pgm: Provided sample test images.
  
  ********** Part 1 ***********  

  c) h1.cc :  Solution for Problem 1.
              File that takes a greyscale image and an output file name. Then, it locates edges in the input image
              and outputs a gret level edge image.
  
  d) hough_complex_1_part1.pgm | hough_simple_1_part1.pgm | hough_simple_2_part1.pgm: Output images from h1.cc. 
   
  ******************************

  *********** Part 2 ***********
  e) h2.cc :  Solution for Problem 2.
              File that takes a gray-level edge image, a gray level threhold and output binary image.
              Uses the threshold to turn edge image to binary.
              THRESHOLD USED: 24

  f) hough_complex_1_part2.pgm | hough_simple_1_part2.pgm | hough_simple_2_part2.pgm: Output images from h2.cc. 
   
  ******************************

  *********** Part 3 ***********
  g) h3.cc :  Solution for Problem 3.
              File that takes binary edge image and outputs gray level hough image and hough voting array.
              Program performs hough transformation on the input binary image and craetes its voting array.
              IMAGE SIZE USED: Same as input image size. 

  h) hough_complex_1_part3.pgm | hough_simple_1_part3.pgm | hough_simple_2_part3.pgm: Output images from h3.cc. 
   
  i) hough_complex_1_part3_votingarray.txt | hough_simple_1_part3_votingarray.txt | hough_simple_2_part3_votingarray.txt: 
      Text Database outputs from h3.cc. Contains information stated in (i) separated by spaces. 
  
  ******************************

  *********** Part 4 ***********
  
   j) h4.cc :  Solution for Problem 4.
               Program that take original gray-level image, the voting array and a threhold value to get an output gray level
               line image.
               THRESHOLD USED: 100

   k) hough_complex_1_part4.pgm | hough_simple_1_part4.pgm | hough_simple_2_part4.pgm: Output images from h4.cc. 
  
  ******************************
   p) Makefile: Makefile modified for compiling all four programs.

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
	
	./h1 {input gray-level image} {output gray-level edge image}

   Program 2
   =========
   Instructions to run Program 2 after compilation,
	
	./h2 {input gray-level image} {input gray-level threshold} {output binary image}

   Program 3
   =========
   Instructions to run Program 3 after compilation,
	
	./h3 {input binary edge image} {output gray-level Hough image} {output Hough-voting-array}

   Program 4
   =========
   Instructions to run Program 4 after compilation,
	
	./h4 {input original gray-level image} {input Hough-voting-array} {input Hough threshold value} {output gray-level line image}

----------------------

4) Input Files and Output Files given,

   For input and output files, reference pgm images and .txt databases in Part 1 of this document.

----------------------