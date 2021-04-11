#include "covidSpread.h"

covidSpread::covidSpread() :g_(), total_visited(0) {
    country_ = "China";
    startingVertex = g_.getVertex("PEK");
}

covidSpread::covidSpread(string airport) : g_(), total_visited(0) {
    country_ = "China";
    for_each(airport.begin(), airport.end(), [](char & c) {c = toupper(c);});
    startingVertex = g_.getVertex(airport);
}

covidSpread::covidSpread(string airport, string country) : g_(country), total_visited(0) {
    country_ = country;
    for_each(airport.begin(), airport.end(), [](char & c) {c = toupper(c);});
    startingVertex = g_.getVertex(airport);
}

Vertex* covidSpread::getNextDest(Vertex* start, vector<Vertex*> airports) {
    Vertex* dest = nullptr;
    int rdest = rand() % airports.size();
    if(airports[rdest]->IATA != start->IATA){
        dest = airports[rdest];
    } else {
        while(airports[rdest]->IATA == startingVertex->IATA) {
            rdest = rand() % airports.size();
        }
        dest = airports[rdest];
    }
    return dest;
}

Graph covidSpread::covidsimulation(long limit, int rate) {
    Graph ret = Graph(country_, true);
    vector<Vertex*> airports = g_.getOpenAirports();
    queue<Vertex*> next_starting;
    Vertex* source = nullptr; 
    Vertex* dest = nullptr; 
    int n = 1;
    next_starting.push(startingVertex);

    
    while(!next_starting.empty()) {
        source = next_starting.front(); next_starting.pop();
        for(int i = 0; i < n; i++) {
            // cout << source->IATA << endl;
            dest = getNextDest(source, airports);
            next_starting.push(dest);
            vector<Vertex*> path = g_.aSearch(source->IATA, dest->IATA).first;
            ret.addEdges(path); 
            total_visited += path.size() - 1;
            total_infected += n * (path.size()-1);

        }
        if(total_visited > limit) {return ret;}
        n = rate;
    }

    return ret;
}


//Createa PNG file from the graph generated after the simulation
void Graph::savePNG(string title) {
    std::ofstream neatoFile;
    string filename = title + ".dot";
    neatoFile.open(filename.c_str());
    if (!neatoFile.good())
        cout<<"couldn't create .dot file"<<endl;
    //similar to how lab_ml creates the output graph
    //beginning portion of the graph file syntax
    neatoFile
        << "graph{\n"
        << "\tgraph [overlap_scaling=3, pack=90]\n"
        << "\tnode [label=\"\\N\", width=\"0.001\", height=\"0.001\", margin=\"0.001\"]\n"
        << "\tgraph [bb=\"0,0,7500,5000\"]\n";

    // ADDING AIRPORTS
    vector<pair<string, pair<int, int> > > airports = recordByNation("../datafile/airports.dat.csv", "China"); 
    //gets all the airports from china (to show a map, regardless of whether that airport is visited or not)
    vector<pair<int, int>> XYduplicate; //this is created to slightly adjust repeated xy coordinate values
    for(unsigned i = 0; i < airports.size(); i++) {
        int yposition = 20*airports[i].second.first;
        int xposition = 20*airports[i].second.second;
        pair<int, int> XYpair = make_pair(yposition, xposition);
        if(std::find(XYduplicate.begin(), XYduplicate.end(), XYpair) != XYduplicate.end()){
            yposition -= 10; //in case of repeated coordinate, slightly adjust yposition downward
        }
        else {
            XYduplicate.push_back(make_pair(yposition, xposition)); 
                //store in the created vector to record already-existing XY coordinate pair
        }
        //Writing into the .dot file
        neatoFile << "\t" << airports[i].first << " [label=" << airports[i].first << ", " 
                << "group=" << i << ", fontsize=6, " << "pos=\""
                << xposition << "," 
                << yposition << "\"];" 
                << endl;
    }
    //After all the vertices are created, now we take the vertices visited and edges created in the simulation
    //and store it in vector
    vector<Edge> edge = getEdges();

    /**
     * color decision - use vector to find the largest weight (double max), and assign darker color for 
     * larger edge weight. 
     */
    string color;
    vector<double> frequency_list;
    for(unsigned i = 0; i < edge.size(); i++) {
        frequency_list.push_back(edge[i].frequency);
    }
    double max = *std::max_element(frequency_list.begin(), frequency_list.end());


    //ADDING ROUTES
    vector<string> checkDuplicates; //another vector to remove repeated routes (undirected)
    for(unsigned i = 0; i < edge.size(); i++) {
        string temp = edge[i].source->IATA + "--" + edge[i].dest->IATA;
        string temp2 = edge[i].dest->IATA + "--" + edge[i].source->IATA;
        //need two routes (forth and back) to remove duplicates since the graph is undirected
        if(std::find(checkDuplicates.begin(), checkDuplicates.end(), temp) != checkDuplicates.end()
            || std::find(checkDuplicates.begin(), checkDuplicates.end(), temp2) != checkDuplicates.end()) 
            {
            continue;
            }
        else{
            checkDuplicates.push_back(temp);
            checkDuplicates.push_back(temp2);    
            }  
        double weight = edge[i].frequency;
        if(edge[i].source->IATA==edge[i].dest->IATA) continue; // eliminate self-loops

        //Color decision function - since some vertices have abnormally large edgeweight compared to others,
        //The ratio is scaled differently
        if(weight < max/10)         color = "#FF9D00"; //Lighter Red
        else if(weight < max*2/10)  color = "#FF7400";
        else if(weight < max*3/10)  color = "#FF5E00";
        else if(weight < max*4/10)  color = "#FF3400";
        else                        color = "#FF0000"; //Red
        
        //writing into file
        neatoFile << "\t" << edge[i].source->IATA << "--" << edge[i].dest->IATA <<" ["
                << "color=\"" << color << "\""
                <<", penwidth=" << sqrt(weight/2) << ", style=filled, fillcolor=\"#FCD975\""
                << "];"<<endl;
    }
    neatoFile << "}";
    neatoFile.close();

    //system command to automatically convert to .SVG output
    string command = "gvmap -e " + filename + " | neato -Ecolor=\"#55555522\" -n2 -Tsvg > " + title
                     + ".svg 2> /dev/null";
    int result = system(command.c_str());
    if (result == 0) {
        cout << "Output graph saved as " << title << ".svg" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }
}

