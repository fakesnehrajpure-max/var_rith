DSA ANSWERS (C), grouped by topic
Compile any file:  gcc -Wall filename.c -o run   then   ./run
Every file starts with its question as a /* comment */, then includes, typedef struct,
function declarations, main, and function definitions below main.
Every program compiles with gcc -Wall -Wextra with no warnings, and was run with
valgrind (no memory leaks, no invalid reads or writes).

01_Arrays                 array menu (insert, delete, min, max, avg, duplicates, reverse), employee structure,
                          dynamic memory (1D, 2D contiguous, 2D jagged, array of structs), pth factor, count duplicates
02_Searching              linear search (iterative + recursive, duplicates), binary search (sorted insert, no duplicates)
03_Sorting                bubble / insertion / selection menu, merge sort (two lists), quick sort, heap sort
04_Single_Linked_List     all 12 operations from the linked list assignment,
                          linked list as a struct (Day 6 Q3; C has no classes),
                          employee + project lists (Day 10 sample exam question)
05_Double_Linked_List     add/delete at start, end and middle, display both directions
06_Circular_Linked_List   singly circular list: add/delete at start and end, display
07_Stack                  stack using array, A-Z char stack reversed, stack as a struct with runtime size
                          (Day 6 Q2; C has no classes), stack using linked list
08_Queue                  linear queue, circular queue, queue using linked list
09_Binary_Search_Tree     add, search, delete, pre/in/post-order
10_AVL_Tree               insert, LL/RR/LR/RL balancing, search, delete
11_Hashing                hash array of size 10 (linear probing), hashmap with chaining (duplicates allowed)
12_Mixed_Scenario_Questions
                          scenario questions (question is written at the top of each file):
                          arrays (sensor log), searching (roll numbers), sorting (exam rank list),
                          single LL (playlist), double LL (browser history), circular LL (round robin),
                          stack (brackets + postfix), queue (printer), BST (library), AVL (sorted input),
                          hashing (frequency + two-sum), all-in-one (hospital: hash + heap + stack + list)

Changes from the C++ version
- All 38 programs rewritten in C (new, delete, cout, cin, string, class, bool, templates removed)
- stack_using_class.cpp            -> 07_Stack/stack_using_struct.c
- single_linked_list_class.cpp     -> 04_Single_Linked_List/single_linked_list_struct.c
- new: 04_Single_Linked_List/employee_project_lists.c (Day 10 sample question)
- hashmap_with_chaining uses int keys (C has no string type for keys)
