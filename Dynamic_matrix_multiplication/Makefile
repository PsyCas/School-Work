########################################
##
## Makefile
## LINUX compilation 
##
##############################################


#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.


#Rule for .cpp files
# .SUFFIXES : .cc.o 

.cc.o:
	g++ $(C++FLAG) $(INCLUDES)  -c $< -o $@



#Including
INCLUDES=  -I. 

LIBS_ALL =  -L/usr/lib -L/usr/local/lib $(MATH_LIBS) 


#ZEROTH PROGRAM
ALL_OBJ0= optimal_multiplications.o
PROGRAM_0= optimal_multiplications
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)


#Compiling all
all: 	
		make $(PROGRAM_0)


run_optimal_multiplications: 	
		./$(PROGRAM_0) dimensions_file.txt

#Clean obj files
clean:
	(rm -f *.o; rm -f $(PROGRAM_0); rm -f $(PROGRAM_1); rm -f $(PROGRAM_2)); 

(: