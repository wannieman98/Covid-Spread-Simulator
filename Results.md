# CS225 Final Project Results

To begin, our initial project goal was to find out how many people would be infected with covid-19 in a given time if a traveler who has the disease decided to travel. We used the openflights data of airports, which contains all the airports over the world and the routes that connect them. Since there are 235 airports and 6877 routes only within China, we decided that it was enough to conduct our tests in only China; however, as you can find in Readme, you can choose any other country of your interest.

However, as we started digging into the topic, we thought that employing A* search algorithm will improve the efficiency of the program as it looks for the minimum cost vertex to expand as opposed to dijkstra's algorithm which searches through every single airport. We,therefore, decided to use A* search as our undiscovered topics in class and just use graph visualization to show the result. 

Addtionally, we altered our design a little to mark the end of the procedure with the limit to the number of airports by the infected given as a parameter. The infection rate(# of people infected per 1 person) can also be modified by user input.  

For BFS,dijkstra, and A* search, we created appropriate test cases for each algorithm
For BFS, we tested if BFS properly traverses through the entire graph by checking if every vertex is visited at least once. We also tested the edge case where the source vertex is a closed airport(no routes coming in or out of the airport).
For dijkstra, we tested if the algorithm returns correct distance between two points with 0 transfer, 1 transfer, and multiple transfers.
For A* search, we also tested if the algorithm returns correct distance between two points with 0 transfer, 1 transfer, and multiple transfers. Addtionally, we checked if A* search returns the correct vector of vertex pointers(path taken). 
We used the same condition for dijkstra and A* search algorithm as they should return the same value. 

Moreover, we also compared  the runtime of dijkstra and a* search algorithm. We expected the a* search algorithm to be faster. With the source and destination vertex, "PEK" and "SJW" respectively, the runtime of dijkstra was 6080ms while A* search took 1365 ms. The results corresponded to our expectations. 

At last, we checked for memory leakage or errors and found none.

For the graph implementaion part, we initially chose Force-directed graph to implement the visualization, but later decided to use Graphing onto map based on data because we thought that it would be a better representation if we take the values of longitude and latitudes to specify the position of each airport's node. 
This is achieved in a similar way to how lab_ml implements the output graph, using Neato. 
Different # of airport visited limits are set, with different infection rate. 
Note that different infection rate only influences the total number of people infected, but not the graphical complexity. The larger the limit is, more airports the infected can visit, meaning that there should be more edges on the graph. 
Overall edgeweights are determined so that larger edgeweights are represented with darker red color, and smaller ones are with light red color. 

With the provided sample simulation images, we can clearly see that there are more edges as we set higher limit. Also, each run will result in different output, since each time the infected person travels to a random airport that has a route available. 




