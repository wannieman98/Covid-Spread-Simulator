/**
 * @file from_file.cpp
 * 
 * Implementation of file recorder functions.
 */
#include "from_file.h"
#include <map>

/**
 * gets the informations of airports by nation.
 * 
 * @param file_name
 * @param nation
 * 
 * @return vector of ints and pairs of two strings.
 */
vector<pair<string, pair<int, int> > > recordByNation(const string & file_name, string nation) {
    vector<pair<string, pair<int, int> > > record;

    ifstream file; file.open(file_name);

    string f1, airport_name, f3, f6, country, IATA, lat, longt, f9; //sections of the information for lines.
    while(getline(file, f1, ',')) {
        getline(file, airport_name, ','); // get airport_name
        getline(file, f3, ','); 
        getline(file, country, ','); // get country name
        getline(file, IATA, ','); //get IATA
         getline(file, f6, ','); 
         getline(file, lat, ','); getline(file, longt, ','); // gets longtitude and lattitude
         getline(file, f9, '\n');
        country.erase(remove(country.begin(), country.end(), '"'), country.end());

        if(country == nation) {
            // erases the "" on the strings.
            // airport_name.erase(remove(airport_name.begin(), airport_name.end(), '"'), airport_name.end());
            IATA.erase(remove(IATA.begin(), IATA.end(), '"'), IATA.end());

            //change lattitude to longtitude to int
            stringstream lat_s(lat); stringstream longt_s(longt);
            int lattitude = 0, longtitude = 0;
            lat_s >> lattitude; longt_s >> longtitude;

            // if IATA is not NULL "\N"
            if(IATA.length() >= 3) {
                pair<int, int> nums = make_pair(lattitude, longtitude);

                pair <string, pair<int, int> > temp;
                temp = make_pair(IATA, nums);
                
                record.push_back(temp);
            }
        }
    }
    return record;
}

// /**
//  * gets the informations of all the airports.
//  * 
//  * @param file_name
//  * 
//  * @return vector of ints and pairs of two strings.
//  */


/**
 * picks teh routes within desired countries
 * 
 * @param file_name
 * @param countries
 * 
 * @return returns a vector of pairs with wanted sources and destinations.
 */
vector<pair<string, string> > recordRoutes(const string & file_name, vector<pair<string, pair<int, int> > > airports) {
    vector<pair<string, string> > record;
    map<string, bool> hash;
    for(unsigned i = 0; i < airports.size(); i++) {
        string temp = airports[i].first;
        hash[temp] = true;
    }

    ifstream file; file.open(file_name);

    string f1, f2, source, f4, dest, f6;

    while(getline(file, f1, ',')) {
        getline(file, f2, ','); getline(file, source, ','); getline(file, f4, ','); getline(file, dest, ','); getline(file, f6, '\n');
        auto sit = hash.find(source); auto dit = hash.find(dest);
        if(sit != hash.end() && dit != hash.end()) {
            pair<string, string> temp = make_pair(source, dest);
            record.push_back(temp);
        }
    }
    return record;
}
