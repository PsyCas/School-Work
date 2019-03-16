decision = "y"
total = 0
while decision == "y":
    price = eval( input ( "Enter item price: "))
    total += price
    decision = str ( input ( "Enter another price? (y/n): "))
    decision = decision.lower()
    if decision == "y" or decision == "n":
        print()
    else:
        print ( "\nInvalid input! " )
        start = str ( input ("\nDo you want to start all over again? (y/n) "))
        start = start.lower()
        if start == "y":
             print ()
             decision = "y"
             total = 0
        else:
            total = 0
            print ("\nProgram shutting down\n")

total += total * 0.11
print ( "Total Price: \t  $","{0:.2f}".format(total))

i = input ( "Press enter to shut this program..." )    
