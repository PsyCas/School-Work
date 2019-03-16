string = str ( input ("Enter any word: "))
l = len ( string )
if l%2 != 0:
    a = int (l/2) + 1
else:
    a = l / 2
a -= 1
b = 2
c = 3
w1 = string [0]
while a != 0:
    a -= 1
    w = string [b : c]
    w1 = w1 + w
    b += 2
    c += 2

print ("\n"+w1)
i = input ( "\nPress enter to exit...")
