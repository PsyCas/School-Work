## Author: Parakram Basnet
## Due Date: October 29
## Class: CSCI 2000 Section: 44306
## Instructor: Ms. Greer
## Program Assignment: 4
## Program Title: State Income Tax
##
## Program Description: This program calculates the state income tax. It 
## first asks the user to input their taxable income. Then it compares the 
## the different fields and assigns tax with respect to the taxable 
## income.
##
## Plagiarism Statement:
## I swear that I have not received or given aid on this program
## beyond guidelines of the course including giving or receiving
## specific code content.

#Obtain input from user and store it in the variable "income"

income = int ( input ( "Enter your taxable income (-1 to quit): "))


#Starting loop

while income != -1:                  #Setting sentinel value as -1 so that the loop continues until the sentinel value is the input

    if income <= 20000:              #First condition

        tax = 0.02 * income          #If true, then this statement gets processed

    elif income <= 50000:            #Second condition  

        tax = 400 + 0.025 * (income - 20000)             #If second condition is true, then this statement gets processed

    else:

        tax = 1150 + 0.035 * (income - 50000)            #If every statement is false then this gets processed


    #Displaying output

    print ("Your tax is $" ,"{0:,.0f}".format(tax) , "." , sep = "")


    #Asking input again for it to be executed inside the loop
    
    income = int ( input ( "\nEnter your taxable income (-1 to quit): "))
