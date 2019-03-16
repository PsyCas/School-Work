I = str ( input ( "Enter any word: "))
l = len ( I ) - 1
c = 1
w1 = I [0]
while l != 0:
    c += 1
    w2 = I [0:c]
    w1 = w1 + w2
    l = l - 1

print ( w1 )
P = input ("Press enter to exit" )
    
    
