  
#include "Graph.h"

Graph::Graph() {
    vector<pair<string, pair<int, int> > > airports = recordByNation("../datafile/airports.dat.csv", "China"); //gets all the airports from china
    for(unsigned i = 0; i < airports.size(); i++) {
        Vertex* temp = new Vertex(airports[i].first, airports[i].second.first, airports[i].second.second);
        for_memory.push_back(temp);
        insertVertex(temp);
    }

    vector<pair<string, string> > routes = recordRoutes("../datafile/routes.dat.csv", airports); // gets all the routes within the above airports
    for(unsigned i = 0; i < routes.size(); i++) {
        Vertex* source = getVertex(routes[i].first);
        Vertex* dest = getVertex(routes[i].second);
        insertEdge(source, dest);
    }

    for(auto i = adjacency_list.begin(); i != adjacency_list.end(); i++) {
        if(i->second.empty()) {
            i->first->isClosed = true;
        }
    }
}

Graph::Graph(string country) {
    country[0] = toupper(country[0]);
    for(unsigned i = 1; i < country.length(); i++) {country[i] = tolower(country[i]);}
    vector<pair<string, pair<int, int> > > airports = recordByNation("../datafile/airports.dat.csv", country);
    for(unsigned i = 0; i < airports.size(); i++) {
        Vertex* temp = new Vertex((airports[i]).first, airports[i].second.first, airports[i].second.second);
        for_memory.push_back(temp);
        insertVertex(temp);
    }

    vector<pair<string, string> > routes = recordRoutes("../datafile/routes.dat.csv", airports); // gets all the routes within the above airports
    for(unsigned i = 0; i < routes.size(); i++) {
        Vertex* source = getVertex(routes[i].first);
        Vertex* dest = getVertex(routes[i].second);
        insertEdge(source, dest);
    }

    for(auto i = adjacency_list.begin(); i != adjacency_list.end(); i++) {
        if(i->second.empty()) {
            i->first->isClosed = true;
        }
    }
}

Graph::Graph(string country, bool empty) {
    country[0] = toupper(country[0]);
    for(unsigned i = 1; i < country.length(); i++) {country[i] = tolower(country[i]);}
    vector<pair<string, pair<int, int> > > airports = recordByNation("../datafile/airports.dat.csv", country);
    for(unsigned i = 0; i < airports.size(); i++) {
        Vertex* temp = new Vertex((airports[i]).first, airports[i].second.first, airports[i].second.second);
        for_memory.push_back(temp);
        insertVertex(temp);
    }
}

Graph::~Graph() {
    clear();
}

void Graph::clear() {
    for(Vertex* i : for_memory) {
        delete i;
        i = nullptr;
    }
}

vector<Edge> Graph::getEdges() const {
    if(adjacency_list.empty()) {
        return vector<Edge>();
    }

    vector<Edge> ret;
    set<pair<Vertex*, Vertex*>> seen;
    for(auto i = adjacency_list.begin(); i != adjacency_list.end(); ++i) {
        Vertex* source = i->first;
        for(auto j = i->second.begin(); j != i->second.end(); ++j) {
            Vertex* dest = j->first;
            if(seen.find(make_pair(source, dest)) == seen.end()) {
                ret.push_back(adjacency_list[source][dest]);
                seen.insert(make_pair(source, dest));
            }
        }
    }
    return ret;
}

unordered_map<Vertex*,vector<Vertex*>> Graph::breadthfirstsearch(string IATA){
    unordered_map<Vertex*, vector<Vertex*>> out;
    Vertex* source = this->getVertex(IATA);
    if(source->isClosed){
        cout<<"CLOSED"<<endl;
        return out;
    }
    queue<Vertex*> tempq;
    unordered_map<Vertex*, bool> isVisited;
    unordered_map<Vertex*, bool> alreadyinq;
    for(auto i = adjacency_list.begin();i!=adjacency_list.end();++i){
        if(!i->second.empty()){
            isVisited[i->first] = false;
            alreadyinq[i->first] = false;
            Vertex* temp = i->first;
            out[i->first].push_back(temp);
        }
    }

    tempq.push(source);
    while(!tempq.empty()){
        Vertex* one = tempq.front();
        tempq.pop();
        if(isVisited.at(one) == false){
            for(auto i = adjacency_list[one].begin(); i != adjacency_list[one].end();++i){
                if(isVisited.at(i->first) == false && !alreadyinq[i->first]){
                    tempq.push(i->first);
                    alreadyinq[i->first] = true;
                    vector<Vertex*> tempvec;
                    for(Vertex *it : out[one]){
                        tempvec.push_back(it);
                    }
                    tempvec.push_back(i->first);
                    out[i->first] = tempvec;
                }
            }
        }
        isVisited.at(one) = true;
    }

    return out;
}


unordered_map<Vertex*, vector<Vertex*> > Graph::dijkstra(string IATA) const {
    Vertex* source = this->getVertex(IATA);
    vector<Vertex*> V = this->getVerticies();
    unordered_map<Vertex*, vector<Vertex*> > ret;
    unordered_map<Vertex*, int> dist;
    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<pair<int, Vertex*> > > Q;
    if(source->isClosed) {
        cout << "This is a closed airport, there are not routes available." << endl;
        return ret;
    }
 
    for(Vertex* i : V) {
        if(!i->isClosed) {
        ret[i] = vector<Vertex*>();
        ret[i].push_back(source);
        dist[i] = INT_MAX;
        }
    }
    dist[source] = 0;
    Q.push(make_pair(0, source));

    while(!Q.empty()) {
        Vertex* u = Q.top().second;
        Q.pop();
        for(Vertex * v : getAdjacent(u)) {
            int distance = dist[u] + getEdgeWeight(u, v);
            if(distance < dist[v]) {
                dist[v] = distance;
                Q.push(make_pair(dist[v], v));
                vector<Vertex*> tempvec;
                for(Vertex *it : ret[u]){
                    tempvec.push_back(it);
                }
                tempvec.push_back(v);
                ret[v] = tempvec;
            }
        }
    }
    
    return ret;
}

unordered_map<Vertex*, int> Graph::dijkstra_weight(string IATA) const {
    Vertex* source = this->getVertex(IATA);
    vector<Vertex*> V = this->getVerticies();
    unordered_map<Vertex*, vector<Vertex*> > ret;
    unordered_map<Vertex*, int> dist;
    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<pair<int, Vertex*> > > Q;
    if(source->isClosed) {
        cout << "This is a closed airport, there are not routes available." << endl;
        return dist;
    }
 
    for(Vertex* i : V) {
        if(!i->isClosed) {
        ret[i] = vector<Vertex*>();
        ret[i].push_back(source);
        dist[i] = INT_MAX;
        }
    }
    dist[source] = 0;
    Q.push(make_pair(0, source));

    while(!Q.empty()) {
        Vertex* u = Q.top().second;
        Q.pop();
        for(Vertex * v : getAdjacent(u)) {
            int distance = dist[u] + getEdgeWeight(u, v);
            if(distance < dist[v]) {
                dist[v] = distance;
                Q.push(make_pair(dist[v], v));
                vector<Vertex*> tempvec;
                for(Vertex *it : ret[u]){
                    tempvec.push_back(it);
                }
                tempvec.push_back(v);
                ret[v] = tempvec;
            }
        }
    }
    for(auto i = dist.begin(); i != dist.end(); i++) {
        vector<Vertex*> a = ret[i->first];
        
        for(unsigned i = 0 ; i<a.size()-1;i++){
            cout<<a[i]->IATA<<"-->";
        }
        cout << a[a.size()-1]->IATA << " distance is: " << i->second << endl;

    }
    return dist;
}

int Graph::distance(Vertex* source, Vertex* dest){
    int weight = sqrt((source->longitude -dest->longitude)*(source->longitude -dest->longitude)+ (source->latitude -dest->latitude)*(source->latitude -dest->latitude));
    return weight;
}


pair<vector<Vertex*>,int> Graph::aSearch(string start, string dest) {
    Vertex* source = this->getVertex(start);
    vector<Vertex*> V = this->getVerticies();
    pair<vector<Vertex*>,int> out;
    unordered_map<Vertex*, vector<Vertex*>> ret;
    unordered_map<Vertex*, int> distTodest;
    unordered_map<Vertex*, int> dist;
    unordered_map<Vertex*, int> pathdist;
    priority_queue<pair<int, Vertex*>, vector<pair<int, Vertex*>>, greater<pair<int, Vertex*>>> Q;
    if(source->isClosed) {
        cout << "This is a closed airport, there are not routes available." << endl;
        return out;
    }
 
    for(Vertex* i : V) {
        if(!i->isClosed) {
        ret[i].push_back(source);
        distTodest[i] = distance(source,i);
        dist[i] = INT_MAX;
        }
    }
    dist[source] = 0;
    Q.push(make_pair(0, source));

    while(!Q.empty()) {
        Vertex* u = Q.top().second;
        Q.pop();
        if(u->IATA == dest) {break;}
        for(Vertex * v : getAdjacent(u)) {
            int distance = dist[u] + getEdgeWeight(u, v);
            int heuristic = distTodest[v];
            if(distance < dist[v]) {
                dist[v] = distance;
                Q.push(make_pair(dist[v]+heuristic, v));
                vector<Vertex*> tempvec;
                for(Vertex *it : ret[u]){
                    tempvec.push_back(it);
                }
                tempvec.push_back(v);
                ret[v] = tempvec;                
            }
        }
    }
    
    for(Vertex* i : ret[getVertex(dest)]){
        out.first.push_back(i);
    }
    out.second = dist[getVertex(dest)];
    
    return out;
}

vector<Vertex*> Graph::getOpenAirports() const {
    vector<Vertex*> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++) {
        if(it->first->isClosed == false) {
            ret.push_back(it->first);
        }
    }
    return ret;
}

vector<Vertex*> Graph::getVerticies() const {
    vector<Vertex*> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++) {
        ret.push_back(it->first);
    }
    return ret;
}

vector<Vertex*> Graph::getAdjacent(Vertex *source) const{
    auto lookup = adjacency_list.find(source);
    if(lookup == adjacency_list.end())
        return vector<Vertex*>();

    else
    {
        vector<Vertex*> vertex_list;
        unordered_map <Vertex*, Edge> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}

Edge Graph::getEdge(Vertex *source, Vertex *destination) const {
    if(assertEdgeExists(source, destination, __func__) == false) {
        return Edge();
    }
    Edge e = adjacency_list[source][destination];
    return e;
}

void Graph::setEdgeWeight(Vertex* source, Vertex* destination,int w) {
    if(assertEdgeExists(source, destination, __func__) == false) {
        return;
    }
    Edge newe = Edge(source, destination, w);
    adjacency_list[source][destination] = newe;
}

int Graph::getEdgeWeight(Vertex* source, Vertex* destination) const{
    if(assertEdgeExists(source, destination, __func__) == false) {
        return INT_MIN;
    }
    return adjacency_list[source][destination].get_weight();
}

Vertex* Graph::getVertex(string IATA) const {
    if(assertVertexExists(IATA, __func__) == false) {
        return nullptr;
    }
    Vertex* temp = IATA_map[IATA];
    return temp;
}

void Graph::addEdges(vector<Vertex*> paths) {
    if(paths.size() <= 1) {
        return;
    }
   
    for(unsigned i = 0; i < paths.size()-1; i++) {
        Vertex* source = paths[i];
        Vertex* dest = paths[i+1];
        this->insertEdge(source, dest);
        source = dest;
    }
}

void Graph::insertVertex(Vertex* v) {
    IATA_map[v->IATA] = v;
    adjacency_list[v] = unordered_map<Vertex*, Edge>();
}

void Graph::insertEdge(Vertex* source, Vertex* dest) {

    if(adjacency_list.find(source) != adjacency_list.end() && adjacency_list[source].find(dest) != adjacency_list[source].end()) {
        //already exists
        adjacency_list[source][dest].frequency++;
        return;
    }
    if(adjacency_list.find(source) == adjacency_list.end()) {
        adjacency_list[source] = unordered_map<Vertex*, Edge>(); 
    }
    adjacency_list[source][dest] = Edge(source, dest);
}

bool Graph::vertexExists(string IATA) const {
    return assertVertexExists(IATA, "");
}

bool Graph::edgeExists(Vertex* source, Vertex* dest) const {
    return assertEdgeExists(source, dest, "");
}

bool Graph::assertVertexExists(string IATA, string functionname) const {
    if(IATA_map.find(IATA) == IATA_map.end()) {
        if(functionname != "") {
            cout << "called on invalid airport" << endl;
            return false;
        }
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex* source, Vertex* dest, string functionname) const {
    if(!assertVertexExists(source->IATA, functionname)) {
        return false;
    }
    if(adjacency_list[source].find(dest) == adjacency_list[source].end()) {
        if(functionname != "") {
            cout << "called on invalid route " << source->IATA << " --> " << dest->IATA << endl;
        }
        return false;
    }
    return true;
}

void Graph::print() const {
    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) {
        for(auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            cout << it2->second;
        }
    }
}

// void Graph::savePNG(string title) {
//     std::ofstream neatoFile;
//     string filename = title + ".dot";
//     neatoFile.open(filename.c_str());
//     if (!neatoFile.good())
//         cout<<"couldn't create .dot file"<<endl;
//     neatoFile
//         << "graph{\n"
//         << "\tgraph [overlap_scaling=3, pack=90]\n"
//         << "\tnode [label=\"\\N\", width=\"0.001\", height=\"0.001\", margin=\"0.001\"]\n"
//         << "\tgraph [bb=\"0,0,7500,5000\"]\n";

//     vector<tuple<int, string, pair<int, int> > > airports = recordByNation("../datafile/airports.dat.csv", "China"); //gets all the airports from china
//     vector<pair<string, string> > routes = recordRoutes("../datafile/routes.dat.csv", airports); // gets all the routes within the above airports

//     // ADDING AIRPORTS
//     vector<pair<int, int>> XYduplicate;
//     for(unsigned i = 0; i < airports.size(); i++) {
//         int yposition = 20*(get<2>(airports[i]).first);
//         int xposition = 20*(get<2>(airports[i]).second);
//         pair<int, int> XYpair = make_pair(yposition, xposition);
//         if(std::find(XYduplicate.begin(), XYduplicate.end(), XYpair) != XYduplicate.end()){
//             yposition -= 10;
//         }
//         else {
//         XYduplicate.push_back(make_pair(yposition, xposition));
//         }
//         neatoFile << "\t" << get<1>(airports[i]) << " [label=" <<get<1>(airports[i]) << ", " 
//         // neatoFile << "\t" << getVertex(i) << " [label=" <<get<1>(airports[i]) << ", " 
//                 << "group=1, fontsize=6, "
//                 << "pos=\""<< xposition << "," << yposition << "\"];" << endl;
//     }

//     //ADDING ROUTES
//     vector<string> checkDuplicates;
//     for(unsigned i = 0; i < routes.size(); i++) {
//         string temp = routes[i].first + "--" + routes[i].second;
//         string temp2 = routes[i].second + "--" + routes[i].first;
//         if(std::find(checkDuplicates.begin(), checkDuplicates.end(), temp) != checkDuplicates.end()
//             || std::find(checkDuplicates.begin(), checkDuplicates.end(), temp2) != checkDuplicates.end()) 
//             {
//             continue;
//             }
//         else{
//             checkDuplicates.push_back(temp);
//             checkDuplicates.push_back(temp2);    
//             }  
//         Vertex* source = getVertex(routes[i].first);
//         Vertex* dest = getVertex(routes[i].second);
//         double weight = getEdgeWeight(source, dest);
//         double scaled_weight = 0;
//         if(weight > 1)
//         if(source==dest) continue; // eliminate self-loops
//         neatoFile << "\t" << routes[i].first << "--" << routes[i].second <<"["
//                 //<< "label=\"" << weight << "\", "
//                 << "color=red, penwidth=" << sqrt(weight)/20 << ", style=filled, fillcolor=\"#FCD975\""
//                 << "];"<<endl;
//     }
//     neatoFile << "}";
//     neatoFile.close();
//     string command = "gvmap -e " + filename + " | neato -Ecolor=\"#55555522\" -n2 -Tsvg > " + title
//                      + ".svg 2> /dev/null";
//     int result = system(command.c_str());
//     if (result == 0) {
//         cout << "Output graph saved as " << title << ".svg" << endl;
//     } else {
//         cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
//     }
// }