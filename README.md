# Algorithm Design Project

My course project written in C++ for my bachelor course Algorithm Design at Shiraz University. I've implemented following famous algorithms and data structures:
	
[Depth-First Search](https://en.wikipedia.org/wiki/Depth-first_search)

[Tarjan's algorithm for find strongly connected components](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)

[Dijkstra's algorithm for finding shortest path](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)

[Kruskal's algorithm for finding minimum-spanning-tree](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)

[Binary-Heap data structure](https://en.wikipedia.org/wiki/Binary_heap)

[Disjoint-set data structure](https://en.wikipedia.org/wiki/Disjoint-set_data_structure)
	
# Questions

This project aims to answare some questions regarding a graph. Consider a graph (G) with  unsigned-weighted and directed edges. The **First Task** is to find strongly connected components of the graph.
The **Second Task** is to find the minimum-weighted path between some pairs of vertices. For the **Third Task** consider a new graph with C unsigned-weighted vertices corresponding to each of the C strongly connected components in the G.
Two vertices are connected via a bi-directional edge if their corresponding components were connected in G.
Now consider H(P(v, w)) is the the minimum weight of vertices in a simple path P(v, w) between vertices v and w and F(v, w) is the maximum H(P(v, w)) for any possible P(v, w). 
We want to find the average of F(v, W) over all pairs of vertices in th graph.

# Input and Output format

Input begins with a single line containing two non-negative integers N and M respectively the number of vertices and the number of edges. Followed by N lines, in which the i'th line contains a string which is the name of i'th vertex.
Followed by M lines, one line for each edge consist of two string and a non-negative number, respectively the name of tail and head vertices and the weight of the edge.
Followed by a non-negative integer Q, the number of querries for the second task and Q lines, one for each querry containing two strings the names of the first and last vertices of the path.
Followed by C lines, in which the i'th line contains a string and a non-negative number which are respectively the name of a vertex which previously belonged to the corresponding component and the weight of the i'th vertex in the new graph.

***Input Example***
	
	6 9
	sina
	ali
	kamran
	yoones
	amir
	reza
	sina ali 12
	ali sina 10
	kamran yoones 8
	yoones kamran 5
	amir reza 10
	reza amir 4
	sina yoones 7
	kamran amir 4
	ali reza 5
	3 
	reza ali
	sina amir
	ali amir
	ali 10
	kamran 20
	reza 30

Output begins with the result of first task. Names of vertices of each component seperated by ---. Followed by the result of second task, a line for each querry containing a number which is the sum of th weights on minimum-weighted path, 
or the word "Impossible" if the exist no such a path. Followed by the result of third task, a number in a signle line.

***Output Example***

	sina
	ali
	---
	yoones
	kamran
	---
	amir
	reza
	
	Impossible
	16
	9
	
	13.33333

*Best Regards*