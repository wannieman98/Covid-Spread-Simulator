#include "covidSpread.h"
#include <chrono>

using namespace std::chrono;

int main() {
    // Graph a = Graph(); // constructor for Graph, this sets set the country to "China"

    // ***************************************************************************
    // breadth first search
    // unordered_map<Vertex*, vector<Vertex*> > paths_bfs = a.breadthfirstsearch("PEK");
    // vector<Vertex*> vec_bfs = paths_bfs[a.getVertex("NGQ")];

     // for(Vertex* i : vec_bfs){
    //     cout<< i->IATA << endl;;
    // }

    // ***************************************************************************
    // dijkstra

    // unordered_map<Vertex*, vector<Vertex*> > paths_dij = a.dijkstra("PEK");
    // vector<Vertex*> vec_dij = paths[a.getVertex("NGQ")];

    // for(Vertex* i : vec_dij){
    //     cout<< i->IATA << endl;;
    // }

    // ***************************************************************************

    // ***************************************************************************
    // astar algorithm

    // pair<vector<Vertex*>,int> path_a = a.aSearch("PEK", "NGQ");

    // for(Vertex* i : patha.first) {
    //     cout << i->IATA << endl;
    // }
    // cout << path2.second << endl;

    // ***************************************************************************
    //covidsimulator example
    covidSpread a = covidSpread();
    long limit = 1000;
    int rate = 8;
    Graph ret = a.covidsimulation(limit, rate);
    ret.print();
    string title = "result-limit-" + to_string(limit)+ "infection_rate-" + to_string(rate);
    ret.savePNG(title);
    // cout << "The number of total infected people is " << a.total_infected << endl;
}