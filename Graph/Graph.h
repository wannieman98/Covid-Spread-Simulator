#pragma once

#include <list>
#include <tuple>
#include <unordered_map>
#include <map>
#include <utility>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <climits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>
#include <queue>

#include "edge.h"
#include "from_file.h"
#include <chrono>


using std::map;
using std::cerr;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::string;
using std::to_string;
using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;

class Graph
{
public:
    /**
     * Constructor for Graph
     */
    Graph();

    Graph(string country);

    Graph(string country, bool empty);

    /**
     * Destructor for Graph
     */
    ~Graph();

    /**
     * @param source - IATA of the source vertex
     * Takes the source vertex and performs Breadth First Search.
     * Returns each open airport with its path taken
     * @return unordered map with vertex pointers(airport) as keys and path from the source to each vertex
     */

    unordered_map<Vertex*,vector<Vertex*>> breadthfirstsearch(string IATA);


      /**
     * Gets all adjacent vertices to the parameter vertex.
     * @param source - vertex to get neighbors from
     * @return a vector of vertices
     */
    vector<Vertex*> getAdjacent(Vertex *source) const;

    /**
     * Returns one vertex in the graph. This function can be used
     *  to find a random vertex with which to start a traversal.
     * @return a vertex from the graph
     */
    // Vertex* getStartingVertex() const;

    /**
     * Gets an edge between two vertices.
     * @param source - one vertex the edge is connected to
     * @param destination - the other vertex the edge is connected to
     * @return - if exist, return the corresponding edge
     */
    Edge getEdge(Vertex *source, Vertex *destination) const;

    /**
     * Gets a Vertex of the IATA.
     * @param IATA IATA of the airport
     * @return Pointer to the Vertex
     */
    Vertex* getVertex(string IATA) const;

    /**
     * sets the weight of the edge
     * @param source pointer to the source airport
     * @param destination pointer to the destination airport
     */
    void setEdgeWeight(Vertex* source, Vertex* destination, int w);

    /**
     * Gets the weight of the edge
     * @param source pointer to the source airport
     * @param destination pointer to the destination airport
     * @return returns the weight of the edge
     */
    int getEdgeWeight(Vertex* source, Vertex* destination) const;

    /**
     * Inserts an edge to the graph
     * @param source pointer to the source airport
     * @param destination pointer to the destination airport
     */
    void insertEdge(Vertex* source, Vertex* destination);

    /**
     * Inserts edges to the graph from vector of paths
     * @param paths list of Verticies travelled
     */
    void addEdges(vector<Vertex*> paths);

    /**
     * returns a vector of edges in the graph
     */
    vector<Edge> getEdges() const;

    /**
     * returns a vector of verticies in the graph
     */
    vector<Vertex*> getVerticies() const;

    /**
     * returns a vector of open airports in the Graph
     */
    vector<Vertex*> getOpenAirports() const;

    /**
     * Dijkstra function (Single Source shortest path)
     * @param source
     * @return unordred map of paths to get to the destination from source 
     */
    unordered_map<Vertex*, vector<Vertex*> > dijkstra(string IATA) const;

    /**
     * Dijkstra function
     * @param source
     * @return weights it took to get to the distance from source
     */
    unordered_map<Vertex*, int> dijkstra_weight(string IATA) const;

    /**
     * Gets the distance from the source to the dest.
     * Works even if there is no edge between the two points.
     * @param source
     * @param destination
     * @return distance
     */
    int distance(Vertex* source, Vertex* dest);

    /**
     *  A* search function
     * Finds the shortest path from the source to dest
     * @param source
     * @param destination
     * @return path taken and its distance
     */
    pair<vector<Vertex*>,int> aSearch(string start, string dest);

    /**
     * Inserts a vertex to the graph
     * @param v pointer to the vertex
     */
    void insertVertex(Vertex* v);

    /**
     * Removes a vertex to the graph
     * @param v
     * @return returns a pointer to the removed Vertex
     */
    Vertex removeVertex(Vertex* v);

    /**
     * print the edges of the Graph
     * print source,destination airports,the edge weight and the # of times the path has been taken
     */
    void print() const;
    
    /**
     * function for visualizing Graph
     * 
     * @param title
     */
    void savePNG(string title);

    /** checker function for vertex
     * 
     * @param IATA
     */
    bool vertexExists(string IATA) const;

    /**
     * checker function for edge
     * 
     * @param source
     * @param dest
     */
    bool edgeExists(Vertex* source, Vertex* dest) const;

    /**
     * checking if vertex exists
     * 
     * @param IATA
     * @param functionname
     */
    bool assertVertexExists(string IATA, string functionname) const;

    /**
     * checking if edge exists
     * 
     * @param source
     * @param dest
     */
    bool assertEdgeExists(Vertex* source, Vertex* dest, string functionname) const;

private:
    mutable unordered_map<Vertex*, unordered_map<Vertex*, Edge> > adjacency_list;
    mutable unordered_map<string, Vertex*> IATA_map;
    //Vector used for freeing memory
    vector<Vertex*> for_memory;
    

    void clear();
};