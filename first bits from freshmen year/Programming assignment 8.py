## Author: Parakram Basnet
## Due Date: October 27
## Class: CSCI 2000 Section: 44306
## Instructor: Ms. Greer
## Program Assignment: 8
## Program Title: FunWithFunctions
##
## Program Description: This program asks the user which pattern
## they want displayed and the number of rows of the pattern.
## Then, it prints out the pattern. User inputs 5 to close the
## program.
##
## Plagiarism Statement:
## I swear that I have not received or given aid on this program
## beyond guidelines of the course including giving or receiving
## specific code content.


## Defining the function getChoice () to get choice from user.
def getChoice ():

    ## Asking users choice.
    choice = input ("Enter 1, 2, 3, or 4 to choose a pattern to display. Enter 5 to exit. ")

    ## Setting flag variable 
    Flag = True

    while Flag == True:     ## Initializing while loop

        # Statements to validate the input.

        if not(choice.isdigit()) and not(choice.startswith("-")):               # If choice is a string and not a negative number, this gets executed.

            print ("\nInput must be a number")
            choice = input ("\nEnter 1, 2, 3, or 4 to choose a pattern to display. Enter 5 to exit. ")

        elif int (choice) < 1 or int(choice) > 5:                               # If choice is a negative number or greater than 5, this gets executed

            print ("\nInput must be within choice")
            choice = input ("\nEnter 1, 2, 3, or 4 to choose a pattern to display. Enter 5 to exit. ")

        else:
            Flag = False                                                        # If both conditions are false, Choice is correct. So, loop ends.

    ## Returning the value of choice
    return choice


## Defining the function getRows (choice) to get rows from user.
def getRows (choice):

    ## Setting flag variable for first while loop.
    Flag = True 

    ## Initializing while loop
    while Flag == True: 

        Flag1 = True                   # Setting flag variable for second while loop.

        if choice == "1":              # Gets executed if choice is 1. 

            rows = int (input ("\nPattern 1 How many rows (3-20) "))

        elif choice == "2":            # Gets executed if choice is 2.
            
            rows = int(input ("\nPattern 2 How many rows (3-20) "))

        elif choice == "3":            # Gets executed if choice is 3.
            
            rows = int(input ("\nPattern 3 How many rows (3-20) "))

        elif choice == "4":            # Gets executed if choice is 4.
            
            rows = int(input ("\nPattern 4 How many rows (3-20) "))

        else:                          # The last choice can only be 5, which exits. 

            rows = 5                   # Setting a value on "rows" so something can be returned at the end of function.
            Flag = False               # Ending first loop.
            Flag1 = False              # Not letting this value get put into second while loop.

        ## Initializing second while loop.
        while Flag1 == True:    

            ## Conditions to validate the input.

            
            if rows < 3 or rows > 20:  # Gets executed if user puts incorrect input.      

                print ("\nValues must be between 3 and 20")
                Flag1 = False          # Ends second loop but not first. So, the user is prompted to enter a value again.

            else:                      # Gets executed if input is correct.

                Flag = False           # Since value is correct, ending the first loop. 
                Flag1 = False          # Ending the second loop.

    ## Returning the value of rows.
    return rows                        


## Defining funcion for Pattern1.
def Pattern1 (rows):
    
    for i in range(1, rows + 1 ):               # Outside loop for number of rows.

        for j in range(1, rows + 1):            # Inside loop for number of columns.

            print( "*", end = "" )              # Printing asteriks.

        print()                                 # Breaking a line.

    print ()                                    # Breaking a line.


## Defining function for Pattern2.
def Pattern2 (rows):


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

    print ()                                    # Breaking a line.



## Defining function for Pattern3.
def Pattern3 (rows):
    

    y = rows                                    # Setting a variable with respect to the rows to change later.

    for i in range ( 1, rows + 1):              # Outside loop for the number of rows.
    
        for j in range ( y, 0 , -1):            # Inside loop for the number of columns.
    
            print ( "*", end = "" )             # Printing out the required pattern.

        y -= 1                                  # Decreasing the value of "y" to prevent infinite loop.

        print ()                                # Breaking the line.

    print ()                                    # Breaking a line.

    
## Defining function for Pattern4.
def Pattern4 (rows):
    

    space = " "                                 # Setting a variable for spaces.
    pattern = ""                                # Setting a blank string.
    y = 0                                       # Setting a variable to control the number of spaces.

    for i in range ( 1, rows + 1):              # Outside loop for number of rows.

        for j in range (1 , 3):                 # Inside loop for number of columns.

            pattern = pattern + "*" + space * y # Setting a variable with the required pattern.

        pattern = pattern.rstrip()              # Removing the extra space at the end.
        y += 1                                  # Adding the required space for the next iteration.
        pattern += "\n"                         # Changing the line.

    print ( pattern.rstrip() )                  # Printing the required pattern.

    print ()                                    # Breaking a line.



## Defining the main function. 
def main():

    ## Printing the menu.
    print ("Options:\nPattern 1 \nPattern 2 \nPattern 3 \nPattern 4 \n" )
    
    ## Setting a flag variable.
    Flag = True

    ## Initializing while loop.
    while Flag == True:

        choice = getChoice ()                   # Calling the getChoice () function and setting in variable choice.
        rows = getRows (choice)                 # Calling the getRows (choice) function and setting in variable rows.

        if choice == "1":                       # Gets initialized if choice is 1.
    
            Pattern1(rows)                      # Calling function Pattern1(rows).

        elif choice == "2":                     # Gets initialized if choice is 2.

            Pattern2(rows)                      # Caling function Pattern2 (rows).

        elif choice == "3":                     # Gets initialized if choice is 3.

            Pattern3(rows)                      # Calling function Pattern3(rows).

        elif choice == "4":                     # Gets initialized if choice is 4.

            Pattern4(rows)                      # Calling function Pattern4(rows).

        elif choice == "5":                     # Gets initialized if choice is 5.

            Flag = False                        # Loop ends. End of program.

main ()
