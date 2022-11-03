# AirTrafficController
An application program in C that will allow the employee of the air traffic controller to update the information of the flight and also give them permission to takeoff and landing.  


ABSTRACT:
In the Linked List there will be N such nodes which are for takeoff and  landing The terminal window will be open with a welcome and asking the airline employee to register the flight details. Each node in the list will be holding flight ID, arrival time, departure time.
Once the flight details has been entered the ATC can access to the flight details and give permission to the pilots weather they need to takeoff or land from the runway.


DATA STRUCTURE USED
    • Linked list
    • Structures
    
The Data structures used in the programs are:
    
A. LINKED LIST:

Linked List is a linear data structure and it is very common data structure which consists of group of nodes in a sequence which is divided in two parts. Each node consists of its own data and the address of the next node and forms a chain. Linked Lists are used to create trees and graphs.

Disadvantages of Linked Lists
    • The memory is wasted as pointers require extra memory for storage.
    • No element can be accessed randomly; it has to access each node sequentially.
    • Reverse Traversing is difficult in linked list.

Applications of Linked Lists
    • Linked lists are used to implement stacks, queues, graphs, etc.
    • Linked lists let you insert elements at the beginning and end of the list.
    • In Linked Lists we don't need to know the size in advance.


B. STRUCTURES:

Structure is a collection of different data types under a single name.
For example: You want to store some information about a person: his/her name, citizenship number and salary. You can easily create different variables name cityno to store these information separately.
However, in the future, you would want to store information about multiple persons. Now, you'd need to create different variables for each information per person: name1, citNo1, salary1, name2, citNo2, salary2
You can easily visualize how big and messy the code would look. Also, since no relation between the variables (information) would exist, it's going to be a daunting task.
A better approach will be to have a collection of all related information under a single name Person, and use it for every person. Now, the code looks much cleaner, readable and efficient as well.
This collection of all related information under a single name Person is a structure.

