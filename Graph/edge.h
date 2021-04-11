/**
 * @file Graph.h
 * 
 * header file for Graph class
 */

#pragma once

#include "from_file.h"
#include <math.h>

class Vertex{
    public:
    string IATA;
    int longitude;
    int latitude;
    bool isClosed;

    Vertex () : IATA(""), longitude(-1), latitude(-1), isClosed(false) {}
    Vertex (string name, int lot, int lat) : IATA(name), longitude(lot), latitude(lat), isClosed(false) {}
};

class Edge {
    public:
    Vertex* source;
    Vertex* dest;
    int frequency;

    /**
     *  Default constructor with no parameters
     */ 

    Edge() : source(nullptr), dest(nullptr), frequency(0), weight(0) {}

     /**
     *  Default constructor with source and destination vertices
     *  Automatically sets the weight of the edge by using longitude and latitude 
     */ 

    Edge(Vertex* source, Vertex* dest): source(source), dest(dest), frequency(1) {

        // set distance between two airports
        weight = sqrt((source->longitude -dest->longitude)*(source->longitude -dest->longitude)+ (source->latitude -dest->latitude)*(source->latitude -dest->latitude));
        
    }
    /**
     *  Default constructor with source, destination vertices and distance
     *  Edge's weight is set up with the given value of distance
     */ 

    Edge(Vertex* source, Vertex* dest, int dist): source(source), dest(dest), weight(dist){}

    /**
     *  @return weight of the edge
     */ 

    int get_weight() {
        return this->weight;
    }
    
    /**
     * Overload for the operator <<
     * Prints IATA of the source and destination, the edge weight between two points, and how many times the path has been taken
     */
    friend ostream & operator<<(ostream & out, const Edge& edge) {
        out << edge.source->IATA << " -" << edge.weight << "-> " << edge.dest->IATA << " is frequented: " << edge.frequency << " times." << endl;
        return out;
    }


    private:
    int weight;
};