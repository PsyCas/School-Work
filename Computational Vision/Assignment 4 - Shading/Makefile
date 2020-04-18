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


all: 
	make $(PROGRAM_NAME1) 


clean:
	(rm -f *.o; rm s1)

(:
