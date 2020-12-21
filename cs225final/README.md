# COVIDSpread Simulator
## Goal
A program to demonstrate the danger of travelling when covid-19 is abound. This program will simply demonstrate how easily the covid-19 will spread. If the infected person with covid-19 decides to travel through air. 
##### how it works
The covid simulator chooses a random destination for every infected passenger and if the passenger arrives at the destination, then the passenger infects the other people at the airports, in a given rate, who are about to leave to other places. The path from source airprot to destination airport is found by A* search algorithm. Oncce the number of flights reaches a given limit, then the simulator stops and the number of total infected people as well as the graph of the paths of infected people is returned.

## Table of Contents
* [Build](#build)
* [Usage](#usage)

## Build

### Input File Format
When constructing Graph, it will take in two data files:
```
airports data must include IATA, longtitude and latitudes of each airport locations.
routes data must include IATA of source airports and then the IATA of destination airports.
```
This program is built on data sets given by OpenFlights(https://openflights.org/data.html),
specifically airports.dat and routes.dat
1. *RecordByNation* reads the airport data and the data must have more than 9 columns where the 4th column is the country name, 5th column IATA of the airport, and 7th and 8th column being lattitude and longtitude.         
2. *RecordRoutes* reads the routes data and the dat amust have more than 6 columns where the 3rd column is the source airport's IATA and the 5th column being the destination airport's IATA.

### Structure of Graph class
1. class Vertex: vertex class is a node that holds various informations reagrding the airport.
  - isClosed(bool): if there are not routes to and from the airport, then the airport is closed.
  - frequency(int): number of routes from the airport.
  - **Constructors**
      - Vertex has a default constructor.
      - Vertex has a constructor with parameters, IATA, latitude and longitude.

 2. class Edge: Edge is the route that has source vertex and destingation vertex
   - weight(int): this is the distance between the source airport and the destination airport.
      - the distance formula:  sqrt (long1-long2)^2 + (lat1-lat2)^2
      - conversion to km: **weight = 111km**
   - frequency(int): this is purposely made for covidsimulator function and it is the number of overlapping routes.
   - **Constructors**
      - Edge has a default constructor.
      - Edge has a constructor that takes a pointer to the source Vertex and a pointer to the destination Vertex
   
 3. class Graph
  - graph is represented as an adjacency list using unordered map that takes Vertex* as key and gets the adjacent destinations which then serves as the keys for Edges.
  - **Constructors**
      - graph has a default constructor that will get the informations of airports and routes from China by default.
      - graph also has a constructor that takes a country name as an input and gets the airports and routes of desired nation.
      - graph also has a constructor that takes a country name and a bool as inputs that will create a graph with airports without any edges of the desired nation.
 4. class covidSpread
  - class used to perform the simulation of flights that keeps track of the number of total flights and infected people that started from one airport.
  - **Constructors**
      - covidspread has a default constructor that will get the default constructor and the starting vertex will be Beijing.
      - covidspread has a consttructor with one or two parameter that takes a desired IATA of the airport to set the starting vertex and the country name if given will change the country and get the according graph.
  
  
## Usage
For the main purpose of the goal, you simply need to run on the main.cpp
```
covidSpread example = covidSpread(); //creates an object of covidSpread class
Graph output = example.covidsimulator(limit, rate); // limit is maximum number of flights and rate is the infection rate
output.savePNG(); // this requires graphviz downloaded and outputs the simulation
output.print(); // prints the edges of the output graph
make && ./Graph // running main
```
Other algorithms such as dijkstra and A* search and breadth first search is provided in main.cpp
