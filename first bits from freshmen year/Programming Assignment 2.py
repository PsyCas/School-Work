## Author: Parakram Basnet
## Due Date:   September 8
## Class: CSCI 2000 Section: 44306
## Instructor: Ms. Greer
## Program Assignment: 2
## Program Title: ConvertLengths
##
## Program Description: This program asks the user to
##      enter a whole number of inches and converts that length
##      to feet and inches.  See Figure 2.22 on page 49 for a sample run.
##
## Plagiarism Statement:
##      I swear that I have not received or given aid on this program
##      beyond guidelines of the course including giving or receiving
##      specific code content. 


#Converting length given in inches to feet and inches

#Asking the user to input the inches
number = int ( input ("Enter number of inches: "))

#Calculating the number of feet
feet = int ( number / 12)

#Calculating the inches
inches = number % 12

#Printing the required output
print ( number,"inches is",feet,"feet and",inches,"inches." )
