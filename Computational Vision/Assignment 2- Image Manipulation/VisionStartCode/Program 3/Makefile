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

#Assignment Part 3 (Database)
Cpp_OBJ3= image.o p3.o

PROGRAM_NAME3=p3

$(PROGRAM_NAME3): $(Cpp_OBJ3)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(Cpp_OBJ3) $(INCLUDES) $(LIBS_ALL)


all: 
	make $(PROGRAM_NAME3)


clean:
	(rm -f *.o; rm p3)

(:
