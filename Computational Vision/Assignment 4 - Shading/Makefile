########################################
##
## Makefile
## LINUX compilation 
##
##############################################





#FLAGS
C++FLAG = -g -std=c++11

MATH_LIBS = -lm

EXEC_DIR=.


.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@


#Including
INCLUDES=  -I. 

#-->All libraries (without LEDA)
LIBS_ALL =  -L/usr/lib -L/usr/local/lib 


#Assignment Part 1 (Center and Radius)
Cpp_OBJ1= image.o binaryImages.o s1.o

PROGRAM_NAME1=s1

$(PROGRAM_NAME1): $(Cpp_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ1) $(INCLUDES) $(LIBS_ALL)


#Assignment Part 2 (Normal and Source)
Cpp_OBJ2= image.o s2.o

PROGRAM_NAME2=s2

$(PROGRAM_NAME2): $(Cpp_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ2) $(INCLUDES) $(LIBS_ALL)


#Assignment Part 3 (Find needlemap)
Cpp_OBJ3= image.o s3.o

PROGRAM_NAME3=s3

$(PROGRAM_NAME3): $(Cpp_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ3) $(INCLUDES) $(LIBS_ALL)

#Assignment Part 4 (Find surface albeo)
Cpp_OBJ4= image.o s4.o

PROGRAM_NAME4=s4

$(PROGRAM_NAME4): $(Cpp_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ4) $(INCLUDES) $(LIBS_ALL)


all: 
	make $(PROGRAM_NAME1) $(PROGRAM_NAME2) $(PROGRAM_NAME3) $(PROGRAM_NAME4) 

part1:
	make $(PROGRAM_NAME1)

part2:
	make $(PROGRAM_NAME2)

part3:
	make $(PROGRAM_NAME3)

part4:
	make $(PROGRAM_NAME4)

clean:
	(rm -f *.o; rm s1 s2 s3 s4)

(:
