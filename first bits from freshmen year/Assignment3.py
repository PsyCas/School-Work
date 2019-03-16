## Author: Parakram Basnet
## Due Date: September 29
## Class: CSCI 2000 Section: 44306
## Instructor: Ms. Greer
## Program Assignment: 3
## Program Title: CostOfBagels
##
## Program Description: This program asks the user to enter the
## number of bagels and finds total price by multiplying the
## number of bagels by 75 cents if number of bagels is less than 
## half a dozen and by 60 cents if it is greater than or equals 
## to half a dozen.
##
## Plagiarism Statement:
## I swear that I have not received or given aid on this program
## beyond guidelines of the course including giving or receiving
## specific code content.


# Obtain input from user and store it in the variable "number_of_bagels".

number_of_bagels = int ( input ( "Enter number of bagels: "))


# Declare the variable "total_price"

total_price = 0


# Start the if else statement

if number_of_bagels < 6:          # condition for if statement is set

    total_price = 0.75 * number_of_bagels    # True condition


else:                              

    total_price = 0.60 * number_of_bagels    # False condition


# Printing the total price

print ( "Cost is $","{0:.2f}".format(total_price),".",sep = "")
