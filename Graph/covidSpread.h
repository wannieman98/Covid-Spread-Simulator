#pragma once 

#include "edge.h"
#include "Graph.h"
#include <random>

using namespace std;

class covidSpread {
    public:

    long total_infected = 1;

    /**
     * default constructor, the country will be china and the starting airport will be Beijing.
     */
    covidSpread();

    /**
     * one parameter, the country will be china with the given airport by IATA.
     * 
     * @param IATA IATA of the airport
     */
    covidSpread(string IATA);

    /**
     * two parameter, the country will be the given as well as the airport.
     * 
     * @param IATA IATA of the airport
     * @param country name of the Country
     */
    covidSpread(string IATA, string country);

    /**
     * helper function to get random destination
     * 
     * @param start
     * @param airports
     * @return pointer to destination vertex
     */
    Vertex* getNextDest(Vertex* start, vector<Vertex*> airports);

    /**
     * simulation function for spreading of covid-19 through the flights.
     * 
     * @param limit stopping point once number of aggreated affected people reaches.
     * @param rate infection rate.
     */
    Graph covidsimulation(long limit, int rate);

    /**
     * gets starting vertex
     * @return pointer to the starting vertex
     */
    Vertex* getStartingVertex() {
        return startingVertex;
    }


    
    private:
    string country_;
    Graph g_;
    Vertex* startingVertex;
    long total_visited;
};