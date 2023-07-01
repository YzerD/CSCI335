    To approach this problem, I feel that it's more important to UNDERSTAND the 
problem than being able to solve it. Think about coming up with a "solution"
that doesn't solve the problem. So with that in mind, I first read more
up on Weiss's "big five" to understand what does what in the operation.

    After that, I made myself familar with the files provided to us, reading
through the points2d.h file and the test_points2d.cc file's before coding.
From there, I implemented as the test code called for. Default constructor,
size function, one parameter constructor, overloaded stream insertion 
operator (<<), overloaded stream extraction operator (>>), etc. 

    The most difficult part I found to implement was the stream insertion and 
extractionoperators. For the << operator I wasn't sure how strict the 
formatting of thedisplayed points were, so I probably did more work than what
was neccessary. I had it so if the size_ was zero, it would return an empty 
sequence denoted by "().". The case where there was only one point where the 
point was formatted like "(x, y).". Then for sequences with more than 1 point
the last point would be seperated by ", and ", with every other point being 
seperated by ", ", and the the whole sequences ending off with ".\n". The >> 
operator also posed a challenge because I took into account edge cases and 
invalid inputs. I first accounted for if there was no input (!in) and had it 
display an error message. After that, since the first value of the sequence
is the size (amount of points in the sequence), if the size is equal to 0
it's empty and I set the private data variables accordingly. If it passes this
we would set the size_ var to the size, and set the sequence_ to a dynamically
allocated array with that size. Then, for the length of the size, if there 
aren't enough values to populate the point I had it so it displayed an error
message, and dellalocated the resources used since we previously allocated
a new array object. This has it so if there are values that would go beyond
the size called for in the input, it would skip over it, since we iterate
through the size. The 
(!(in >> some_points.sequence_[i][0] >> some_points.sequence_[i][1]))
as previously mentioned, checks if there are values to properly populate
a 2D point, and if it doesn't it would display the error, deallocate the
resources, and abort. 

    Another slight issue I ran into when implementing the functions was
when I was overloading the + operator. At first I was thinking to change
the larger sequence but quickly realzied in the test code that a + b, into
d = a + b added the points once more than expected. But I resolved this
by creating another Points2D object to store the sum and returned that.

    Other than that, I read a lot of GeekForGeeks on how to overload
operators, and generally for any other topics I needed help on to get ideas.
The other functions in the project were generally straight forward. 
