    For this project, just like the first one I wanted to make myself familiar
with the topics that are associated with this project. For this, it was 
linear probing, quadratic probing, and double hashing. I read up again the
chapter 5 notes on Hashing on these topics to get myself more comfortable
about the operations they perform. Each of the three are variations of open
addressing to resolve collisions. As you can expect linear does this linearly,
checking the next avaiable space in the hash table, and quadratic does this to
the 2nd power, hence the quadratic naming scheme. Then we have double hashing,
which just implements a secondary hash function, independent from the first 
hash function. 
    After reading up on these I started to review the starter code that was 
provided to us. At first it took multiple reads to understand what the purpose
of each function was. It also took a while on what I needed to modify in the
code. But reading through the project specifications, I saw that for the first
part it was the Hash Table statistics. I implemented Accessor functions that
would return the current amount of elements in our table, the size of the
table, the load factor. From then on I realized what I needed to modify, I
needed to have a way that would track the amount of collisions and probes.
Looking at the FindPos function, the logic of it checks while the current
hash index we're looking at isn't empty and isn't the element we're looking
for, go to the next hash index (changes with which method we're using). But,
with this, if it isn't the right spot, that means a collision occurred. So
putting a private data variable (initially int collisions = 0), I put in the
FindPos function collisions++. Then for the number of Probes, I copied the
FindPos function but tweaked it a slight bit. Starting at 1 probe, instead of
collisions++, we would have probe_count++, and return that value at the end.
With that we should have all the neccessary statistics for the frist part of
the project. However, I ran into an error that collisions++ increment was of
read-only location. Reading around, discovered mutable vs read-only and changed
the int collisions = 0 to mutable int collisions = 0. This fixed it and all the
statistics were posted correctly.
    For the other two files, linear and doublehashing I copied all of the 
quadartic functions and made the proper naming adjustments. Instead of the 
offset being 2 like in the quadratic probing, I just incremented the current
position by 1 (current_pos++). For Double I just changed the offset to the 
secondary hash function. For that it was just the formula (R - (hf(x) % R)).
There was also another error I ran into while testing. It was a redefinition
error for the IsPrime and NextPrime functions. I just placed them for the
linear and double as a private method and it didn't cause any issues.
    Now it was time to move onto the spell checker. Breaking it down, we'd
have to store the dictionary file into a hash map. Then reading in the
document, we take a word and run it through our three cases for any errors.
If it has one of the three errors it displays the possible words it can be
from our dictionary. If it doesn't encounter any errors it displays the 
word and that it was correct. Another thing I forgot to mention was that
we first had to remove any puncuation from the word and make it all lower
case. To do this I added functions removePunctuation and convertToLowercase
at the top of the spell_check file. 
    Then we can go onto the cases, case A was adding one character to any 
position. Thinking about it, we'd have to go across the entire length of 
the word, and since we limited the character space to just the lowercase,
we'd have to go through a - z. So this means we can use a double for loop.
Since we know that strings are essentially an array of characters we used
the 3 parameter insert function to check the current index and the current
char if that would show up in the dictionary, if it does, display it, if
not, continue onto the next iteration.
    Case B, Removing one character from the word would iterate over the
entire length of the string, and using the erase function. Initailly, I
only passed in one parameter for this and it was just i (the current index),
in testing I noticed that decisasion wasn't displaying decision as a potential
correction. I realized that the way it was now, it was erase everything after
and then check if that was in the dictionary, to fix this I used the 2nd 
parameter of 1 as the size of how many chars we'd like to delete, looking like
erase(i, 1).
    Case C, Swapping adjacnet characters in the word. Would iterate over the
length of the string minus 1. This is because we want to swap the current
index with the char in the very next index. If the swap was a word present
in our dictionary, display it. If not, continue on until the for loop is 
done executing. 
    I'd say that the hardest part of this project was getting started,
having to familiarize myself with the starter code and what everything
did and it's purpose in relation to the hash map. I had to google why 
the offset += 2 worked for quadratic probing, I kinda get it, but it's
still a little shaky at best. Forgot to mention I had to google what
static_cast <float> was in order to get proper division for the table
statistics. 

Resources:
Chapter 5 Notes
https://www.ibm.com/docs/en/zos/2.4.0?topic=expressions-static-cast-operator-c-only
https://www.geeksforgeeks.org/static_cast-in-cpp/
https://www.geeksforgeeks.org/c-mutable-keyword/
https://www.geeksforgeeks.org/removing-punctuations-given-string/
https://www.geeksforgeeks.org/vector-insert-function-in-cpp-stl/
https://www.geeksforgeeks.org/vector-erase-and-clear-in-cpp/

