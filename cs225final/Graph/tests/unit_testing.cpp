#include "../catch/catch.hpp"

#include "../edge.h"
#include "../Graph.h"
#include "../covidSpread.h"

#include <iostream>

TEST_CASE("BFS traverses through the entire graph"){
    Graph g = Graph();
    unordered_map<Vertex*, vector<Vertex*>> out = g.breadthfirstsearch("PEK");
    for(auto &i : out){
        if(i.first == g.getVertex("PEK")){
            REQUIRE(i.second.size() == 1);

        }else{
         REQUIRE(i.second.size() >= 2);

        }
    }
}

TEST_CASE("BFS::closed airport returns an empty map"){
    Graph g = Graph();
    unordered_map<Vertex*, vector<Vertex*> > example = g.breadthfirstsearch("JSJ");
    unordered_map<Vertex*, vector<Vertex*> > empty;
    REQUIRE( example == empty );
}

TEST_CASE("Dijkstra gets the correct distance for direct flight.") {
    Graph g = Graph();
    unordered_map<Vertex*, int> example = g.dijkstra_weight("PEK");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("KHN"));

    REQUIRE( example[g.getVertex("KHN")] == weight );
}

TEST_CASE("Dijkstra gets the correct distance for one-stop flight.") {
    Graph g = Graph();
    unordered_map<Vertex*, int> example = g.dijkstra_weight("PEK");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("DLC"));
    weight += g.getEdgeWeight(g.getVertex("DLC"), g.getVertex("HDG"));

    REQUIRE( example[g.getVertex("HDG")] == weight );
}

TEST_CASE("[1]Dijkstra gets the correct distance for multiple-stop flight.") {
    Graph g = Graph();
    unordered_map<Vertex*, int> example = g.dijkstra_weight("PEK");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("HET"));
    weight += g.getEdgeWeight(g.getVertex("HET"), g.getVertex("SJW"));

    REQUIRE( example[g.getVertex("SJW")] == weight );
}

TEST_CASE("[2]Dijkstra gets the correct distance for multiple-stop flight.") {
    Graph g = Graph();
    unordered_map<Vertex*, int> example = g.dijkstra_weight("PEK");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("LHW"));
    weight += g.getEdgeWeight(g.getVertex("LHW"), g.getVertex("LXA"));
    weight += g.getEdgeWeight(g.getVertex("LXA"), g.getVertex("NGQ"));


    REQUIRE( example[g.getVertex("NGQ")] == weight );
}

TEST_CASE("A* search gets the correct distance for direct flight.") {
    Graph g = Graph();
    pair<vector<Vertex*>, int> example = g.aSearch("PEK", "KHN");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("KHN"));

    REQUIRE( example.second == weight );
}


TEST_CASE("A* search gets the correct distance for one-stop flight.") {
    Graph g = Graph();
    pair<vector<Vertex*>, int> example = g.aSearch("PEK","HDG");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("DLC"));
    weight += g.getEdgeWeight(g.getVertex("DLC"), g.getVertex("HDG"));

    REQUIRE( example.second == weight );
}

TEST_CASE("[1]A* search gets the correct distance for multiple-stop flight.") {
    Graph g = Graph();
    pair<vector<Vertex*>, int> example = g.aSearch("PEK" , "SJW");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("HET"));
    weight += g.getEdgeWeight(g.getVertex("HET"), g.getVertex("SJW"));

    REQUIRE( example.second == weight );
}

TEST_CASE("[2]A* search gets the correct distance for multiple-stop flight.") {
    Graph g = Graph();
    pair<vector<Vertex*>, int> example = g.aSearch("PEK","NGQ");
    int weight = g.getEdgeWeight(g.getVertex("PEK"), g.getVertex("LHW"));
    weight += g.getEdgeWeight(g.getVertex("LHW"), g.getVertex("LXA"));
    weight += g.getEdgeWeight(g.getVertex("LXA"), g.getVertex("NGQ"));


    REQUIRE( example.second == weight );
}

TEST_CASE("A* search returns correct path between two points") {
    Graph g = Graph();
    pair<vector<Vertex*>, int> example = g.aSearch("PEK","JMU");
    vector<Vertex *> result;
    result.push_back(g.getVertex("PEK"));
    result.push_back(g.getVertex("CIF"));
    result.push_back(g.getVertex("HRB"));
    result.push_back(g.getVertex("JMU"));

    REQUIRE(result == example.first );
}