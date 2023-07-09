    For this project, I started by rereading the Chapter Notes on Priority 
Queues (Heaps) before starting. This project there was no starter files to
skim through so we would have to implement the files from scracth, with the
help of the functions implemented in the notes. The functions that are
provided in the notes are, insert, deleteMin, heapify, percolateDown. Keep
in mind that not all utility functions, constructors, and destructors are 
implemented. Also, these functions are for a Min Heap rather than a Max Heap
which is what we're trying to implement. From the notes I took the layout of
the file with a variable to track the current size in our heap and an array
that holds MAX_SIZE + 1 of template type. The MAX_SIZE + 1 ensures that our
heap is index 1. The reason we index from 1 in a heap is that it makes
computing the children of a node easier. 
    Starting off with a Max Heap I ran into a problem, the element was always
being inserted in the 0 index and when I would call getMax I would get 0. I 
didn't know what caused this, and tried to restart by playing around with a
Min Heap first. I figured if I can get the Min Heap to work, I can just invert
the comparison operators to get a Max Heap. Doing this, the issue was resolved.
So going through the Min Heap functions I used and the testing I did in the
main file, I somehow ran into that same exact problem again. Upon further
inspection, I figured out what was causing it. I had current_size_++ in the 
insert function rather than ++current_size_. I had it as current_size++ because
I thought it made the code look more clean, without realizing that there was
something called pre-increment and post-increment. 
    In addition, to the regular heap functions, I added the Weiss's Big Five
from Project1 to help reinforce the topics from that Project with this one.
The same thing was with Customer class, I had the Big Five (as well as some
other functions for both) and implemented it. I had also implemented a 
display function for the heap that would show the index and if it had any
children. 
    For the third part of the project of modifying the Max Heap class to
store Customers. I removed the template portion and just had a regular
class called Max Heap that would operate on Customer Objects. I had to
change the Comparble to Customer for all instances. Then for every comparison
I had to do .getPriorityLevel() since that was what the priority was going to
be based off now. I also created the vector for the history for when we 
deleteMax in the heap. I also implemented a displayHistory function to show
the contents in there. Another thing I have to mention was that I had to 
overload the << operator, so I referred to Project 1 on how to overload that. 
    I wasn't sure if we wanted to maintain the template implementation of the
MaxHeap class, but I just modified it so that it would accomdate Customer
objects, so for the first 2 test heap functions I had to comment them out. 

Resources Used:
Chapter 6. Priority Queue Notes
https://www.geeksforgeeks.org/pre-increment-and-post-increment-in-c/#