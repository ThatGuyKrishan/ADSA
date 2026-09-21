# Advanced Data Structures and Algorithms Lab

## Project Description
This repository contains the laboratory assignments for the course CS4105/CS4116/CS4125/CS4135 Advanced Data Structures and Algorithms Lab, offered in the Autumn Semester 2026. It is part of the 1st Semester M. Tech program (CSE, ISSE, DSE, AI) at the Department of Computer Science & Engineering, NIT Jamshedpur.

## Instructions & Constraints
* **Language:** Use only C programming language for solving the problems. No other programming language (C++, Python, Java, etc.) should be used except for the project work in question 35.
* **Robustness:** The program should run without error for all possible input values and should handle illegal input values without generating a run-time error and getting terminated.
* **Input Handling:** Large numbers of input values (such as a 3x4 or larger size matrix) should be read from text files in order to edit input values efficiently for multiple runs.

## Laboratory Assignments

### Set-1
1. Implement a function to convert an infix arithmetic expression involving the operators +, -, /, *, (,) and single digit constant integer operands to postfix expression. Assume usual precedence of operators in the order of /, *, +, and -. Parentheses () are used to override the precedence of operators.
2. Implement a function to read an arithmetic expression (as given in the previous problem) from the command line (C:\> in Windows and $ in Linux) and display the computed value of the expression. For example: At Linux command prompt, `$(23-8)*3+28/4` followed by Enter key displays `52`.

### Set-2
3. Implement the (i) insertion sort, (ii) bubble sort, (iii) selection sort, (iv) shell sort, (v) quick sort, (vi) merge sort, (vii) heap sort, (viii) radix sort, (ix) counting sort, (x) bucket sort, (xi) radix exchange sort, and (xii) address calculation sort.
4. Implement merge sort without using recursion. You may use a stack data structure in order to keep track of dividing and conquering the task. This will be a top-down approach of solving the problem.
5. Implement merge sort without using recursion and without using any stack. You need to use only two nested loops to complete your task. You do not need any stack. You do not need dividing and conquering the task. This will be a bottom-up approach of solving the problem.

### Set-3
6. Implement a circular queue using (a) an array (b) a linked list.
7. Implement a queue using two stacks by Methods-1 (making Push operation costly in terms of time) and by Method-2 (making Pop operation costly).
8. Implement a stack using two queues by Method 1 (making EnQueue operation costly) and by Method 2 (making DeQueue operation costly in terms of time).

### Set-4
9. Implement the preorder traversal algorithm for binary trees without using recursion.

### Set-5
10. Implement the functions createTree(), deleteTree(), insertItem(), deleteItem(), serachItem() for AVL trees, i.e. height balanced binary search trees, red-black trees, B Trees and B+ Trees.

### Set-6
11. Implement Dijkstra's algorithm for the shortest path problem.
12. Implement Prim's algorithm for the minimum spanning tree problem.
13. Implement Kruskal's algorithm for the minimum spanning tree problem.
14. Implement DFS algorithms for graphs. Your function should be able to identify all the tree edges, back edges, forward edges and cross edges.
15. Write a function to identify the largest and smallest cycles in a given directed or undirected graph.
16. Implement Bellman Ford algorithm for the shortest path problem.
17. Implement dynamic programming algorithm of Floyd-Warshall algorithm for the shortest path problem.
18. Implement the 0/1 knapsack problem using the dynamic programming.
19. Implement the 0/1 knapsack problem using the backtracking method.
20. Implement the n-queens problem using the backtracking method.
21. Implement the 15-puzzle problem using the branch and bound method.

### Set-7
22. Implement the coin changing problem using the greedy method.
23. Write a function to implement the job sequencing with deadline problem in which each job has integer deadline and unit processing time.
24. Implement the graph coloring problem using the backtracking method.
25. Write functions to identify all the strongly connected components, biconnected components, articulation points and bridges in a given directed graph.
26. Write a function to perform topological sort on a given directed graph.
27. Write a function to implement the travelling sales person problem. Prepare the table of running time for graphs containing 10, 20, 40, 60 and 100 nodes and draw graph problem-size versus execution time.

### Set-8
28. Write a program for determining whether a graph with n vertices and e edges contains a clique of size m (m <= n). Check for what values of n, e, and m your program gives output in reasonable time.
29. Write a program for determining whether there exists a Hamiltonian cycle in a graph with n vertices and e edges.
30. Write a program for determining whether a graph with n vertices and e edges is a bipartite graph.

### Set-9
31. Implement Rabin Karp string matching Algorithm.
32. Implement Knuth-Morris-Pratt string matching Algorithm.
33. Implement Boyer-Moore string matching Algorithm.
34. Implement Graham scan algorithm or Jarvis March algorithm to find a convex hull of a set of N points whose coordinates are given as (x1, y1), (x2, y2), ..., (xN, yN).

### Set-10
35. Project: Develop a Java based software JEES using GUI interface to process the result of JEE main. Student details should be taken as input when student registers themselves for the examination. JEES assigns them a six character unique Roll number in sequence that also reflects their category. Students belong to Gen and Resrv categories. Roll number serves the purpose of the primary key of a student's record to identify student uniquely. Marks are filled by the office staff. Student can view their result themselves. Merit serial is made based on total score, if total marks are equal then higher rank is decided on Math marks score, then on Phy marks score if Total as well as Math marks of two students are also same.
36. Repeat the above project for a web-based design using any appropriate web design frame work.
