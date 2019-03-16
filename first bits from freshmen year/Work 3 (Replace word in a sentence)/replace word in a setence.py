sentence = str ( input ("Enter a sentence: " ) )

word = str ( input ( "Enter word to replace: " ) )
replace = str ( input ( "Enter replacement word: " ) )

s = sentence.find(word)
l = len(word)
p = s + l

storage = sentence [:s]

sentence = sentence [s:]

s1 =  sentence[l:]

print (storage+ replace+s1)

I = input ("Press any key to exit out: " ) 
