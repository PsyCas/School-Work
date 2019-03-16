price = 0
total = 0
decision = "Y"
while decision == "Y":
    while price != -1 and price >= 0:
        total = total + price
        price = eval ( input ( "Enter item price ( -1 to finish): "))

    if price < 0 and price != -1:
        print ( "\nThe price cannot be a negative number.")
        decision = str ( input ( "\nDo you want to start over?(Y/N) " ))
        decision = decision.upper()
        price = 0
        print()

    else:
        total = total + (total * 0.11)
        decision = "N"
        print ("\nTotal Price:\t$","{0:.2f}".format(total), sep = "")

i = input ("Enter anything to close...")
    
