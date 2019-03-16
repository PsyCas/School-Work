## Author: Parakram Basnet
## Due Date: October 22
## Class: CSCI 2000 Section: 44306
## Instructor: Ms. Greer
## Program Assignment: 7
## Program Title: FunWithNestedLoops
##
## Program Description: Using nested for loops to create four
## patterns of asterisks.
##
## Plagiarism Statement:
## I swear that I have not received or given aid on this program
## beyond guidelines of the course including giving or receiving
## specific code content.


## For Pattern 1

print ()

# Asking input for number of rows for Pattern 1.
rows = int (input ("Pattern 1 How many rows (3-20)? "))

for i in range(1, rows + 1 ):               # Outside loop for number of rows.

    for j in range(1, rows + 1):            # Inside loop for number of columns.
        print( "*", end = "" )              # Printing asteriks.

    print()                                 # Breaking a line.


## For Pattern 2

print ()                                    

# Asking input for number of rows for Pattern 2.
rows = int (input ("Pattern 2 How many rows (3-20)? "))

pattern = ""                                # Setting a blank string.
space = " "                                 # Setting a variable for number of spaces.
y = rows - 1                                # Setting a variable used to control number of spaces.

for i in range (1, rows + 1):               # Outside loop for number of rows.
    
    pattern = pattern + ( space * y)        # Adding spaces to the blank string.

    for j in range (1, i + 1 ):             # Inside loop for number of columns.

        pattern = pattern + "*"             # Adding asteriks to the variable.

    y -= 1                                  # Decreasing the variable by 1.
    pattern += "\n"                         # Changing the line.

print ( pattern.rstrip() )                  # Printing the pattern by removing the last space. 


## For Pattern 3

print ()

# Asking input for number of rows for Pattern 3.
rows = int (input ("Pattern 3 How many rows (3-20)? "))

y = rows                                    # Setting a variable with respect to the rows to change later.

for i in range ( 1, rows + 1):              # Outside loop for the number of rows.
    
    for j in range ( y, 0 , -1):            # Inside loop for the number of columns.

        print ( "*", end = "" )             # Printing out the required pattern.

    y -= 1                                  # Decreasing the value of "y" to prevent infinite loop.

    print ()                                # Breaking the line.


## For Pattern 4
    
print ()

# Asking input for number of rows for Pattern 4.
rows = int (input ("Pattern 4 How many rows (3-20)? "))

space = " "                                 # Setting a variable for spaces.
pattern = ""                                # Setting a blank string.
y = 0                                       # Setting a variable to control the number of spaces.

for i in range ( 1, rows + 1):              # Outside loop for number of rows.

    for j in range (1 , 3):                 # Inside loop for number of columns.

        pattern = pattern + "*" + space * y # Setting a variable with the required pattern.

    pattern = pattern.rstrip()              # Removing the extra space at the end.
    y += 1                                  # Adding the required space for the next iteration.
    pattern += "\n"                         # Changing the line.

print ( pattern )                           # Printing the required pattern.

    

