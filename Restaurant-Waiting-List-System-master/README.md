# C-Restaurant-Waiting-List-System
Restaurant waiting list which simulates the waiting line of a restaurant.

The ADT used is a modified queue where you can push to the back, but can remove an item from any spot.

Terminal Compilation: make

Input:

q - to quit the program

? - to list the accepted commands

a <size> <name> - to add a group to the wait list
  
c <size> <name> - to add a call-ahead group to the wait list
  
w <name> - to specify a call-ahead group is now waiting in the restaurant
  
r <table-size> - to retrieve the first waiting group that can fit at the available table size

l <name> - list how many groups are ahead of the named group
  
d - display the wait list information
