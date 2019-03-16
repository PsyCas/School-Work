gender = str ( input ("Are you a boy or a girl? Press B or G :"))
name = str ( input ("Enter your name :"))
DOB = int ( input ("Enter your year of birth :"))
date = int ( input ("Enter the current year :" ))
age = date - DOB
if gender == "g" or gender== "G" :
    print ( "Hey" , name , "you are" , age , "years young!" )
    print ( "Always stay young!" )
elif gender == "b" or gender == "B" :
    print ( "Hey" , name , "you are" , age , "years old!" )
    print ("You are getting old man, slow down!:")
else:
    print ("At least type your gender right -_-")
print ("Thanks, Bye now!" )
I = input("Press close to exit")
