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


#First Program (ListTest)
Cpp_OBJ=image.o image_demo.o

PROGRAM_NAME=image_demo

$(PROGRAM_NAME): $(Cpp_OBJ)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ) $(INCLUDES) $(LIBS_ALL)


#Assignment Part 1 (BinaryImages)
Cpp_OBJ1= image.o p1.o

PROGRAM_NAME1=p1

$(PROGRAM_NAME1): $(Cpp_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ1) $(INCLUDES) $(LIBS_ALL)

#Assignment Part 2 (Labeling and Segmenting Binary Images)
Cpp_OBJ2= image.o p2.o

PROGRAM_NAME2=p2

$(PROGRAM_NAME2): $(Cpp_OBJ2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Assignment Part 3 (Database)
Cpp_OBJ3= image.o p3.o

PROGRAM_NAME3=p3

$(PROGRAM_NAME3): $(Cpp_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ3) $(INCLUDES) $(LIBS_ALL)

#Assignment Part 3 (Database)
Cpp_OBJ4= image.o p4.o

PROGRAM_NAME4=p4

$(PROGRAM_NAME4): $(Cpp_OBJ4)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ4) $(INCLUDES) $(LIBS_ALL)




all: 
	make $(PROGRAM_NAME) $(PROGRAM_NAME1) $(PROGRAM_NAME2) $(PROGRAM_NAME3) $(PROGRAM_NAME4) 


clean:
	(rm -f *.o; rm image_demo p1 p2 p3 p4)

(:
