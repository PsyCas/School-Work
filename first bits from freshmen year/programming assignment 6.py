## Author: Parakram Basnet
## Due Date: October 15
## Class: CSCI 2000 Section: 44306
## Instructor: Ms. Greer
## Program Assignment: 6
## Program Title: PhoneNumber
##
## Program Description: This program reads phone numbers in a
## ".txt" file and removes the dashes between the phone
## numbers.
##
## Plagiarism Statement:
## I swear that I have not received or given aid on this program
## beyond guidelines of the course including giving or receiving
## specific code content.


# Opening and reading the data from a ".txt" file
infile = open ("PhoneBook.txt","r")

# Skipping a line in the program.
print ()

# Using for loop to read the data in each line.
for line in infile:

    a = line.find("-")           # Finding the location of the first dash. 
    b = line.rfind("-")          # Finding the location of the second dash.

    area_code = line[0:a]        # Storing the area code digits in "area_code".
    last_digits = line[b+1:]     # Storing the last four digits in "last_digits".
    middle_digits = line[a+1:b]  # Storing the middle digits in "middle_digits".

    # Printing the output without the dashes.
    print ("Number without dashes is ",area_code,middle_digits,last_digits.rstrip(),".", sep ="")
    
