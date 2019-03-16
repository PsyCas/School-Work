## Author: Parakram Basnet
## Due Date: October 11
## Class: CSCI 2000 Section: 44306
## Instructor: Ms. Greer
## Program Assignment: 5
## Program Title: CalculateArea
##
## Program Description: This program displays a menu and then
## asks the user to enter a value of 1-4 to. It then reads the value
## and follows the required procedures to print the area of either
## a rectangle, triangle, circle or quit the program. If the
## user enters an invalid value, it displays that the value was
## improper and asks them to enter the value again.
##
## Plagiarism Statement:
## I swear that I have not received or given aid on this program
## beyond guidelines of the course including giving or receiving
## specific code content.



# Setting Flag variable to a Bool data which helps to end the loop later.
flag = True


# Printing out the menu of the program.
print ( "Options:","\n","-"*8, sep = "")

print ("\n1. Area of a Rectangle","\n2. Area of a Triangle","\n3. Area of a circle","\n4. Quit")


# Loop begins when condition is True.
while flag == True:


    # Asking the user which option they want.
    choice = input ( "\nMake a selection from the options menu: ")
    choice = eval (choice)


    # if statement begins.
    if choice == 1:             # Checking if the value entered is 1 to calculate area of a rectangle.

        height = eval ( input ("\nEnter the height of the recatangle: "))         # Asking height of the rectangle.

        width = eval ( input ("Enter the width of the recatangle: "))             # Asking width of the rectangle.

        area = (height * width)                                                   # Calculating area using the formula.


        # Printing the area of rectangle.
        print ("\nThe area of the rectangle is ","{0:.2f}".format(area),".",sep = "")


    # if 1st condition is false, it checks the elif condition.

    elif choice == "2":           # Checking if the value entered is 2 to calculate the area of a triangle.

        base = eval ( input ("\nEnter the value of base of the triangle: "))      # Asking base of the triangle.

        height = eval ( input ("Enter the height of the triangle: "))             # Asking height of the triangle.

        area =  (1/2 * base * height)                                             # Calculating area using the formula.  


        # Printing the area of triangle.

        print ("\nThe area of triangle is ","{0:.2f}".format(area),".",sep = "")


    # if 2nd choice is also false, it check this elif condition.

    elif choice == "3":          # Checking if the value entered is 3 to calculate the area of a circle.

        radius = eval ( input ("\nEnter the radius: "))                           # Asking for radius of the circle.

        area = (3.141592 * radius ** 2)                                           # Calculating area using the formula.

        # Printing the area of circle.

        print ("\nThe area of circle is ","{0:.2f}".format(area),".", sep = "")


    # if 3rd choice is also false, it cchecks this elif condition.

    elif choice == "4":         # Checking if the value entered is 4 to quit the program.

        flag = False            # Changing value of Flag variable to "False" to end the while loop.


    # if the user entered an invalid data, if comes to this else statement.
    else:

        # Printing to let the user know that they have entered invalid data.

        print ("\nYou did not enter a proper number")                            
    
