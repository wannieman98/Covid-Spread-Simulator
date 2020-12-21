/**
 * @file from_file.h
 * Declaration for recording from txt files
 */
#pragma once

#include <utility>
#include <iostream>
#include <string>
#include <complex>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

using std::string;
using std::vector;
using std::cout;
using std::endl;

/**
 * Reads in text files and gets the IATA and airport names.
 * 
 * @param file_name
 * @param nation name of the desired country.
 * 
 * @return returns a vector of pair with ids and pair of IATA and airport names.
 */
// vector<tuple<int, string, pair<int, int> > > recordByNation(const string & file_name, string nation);
vector<pair<string, pair<int, int> > > recordByNation(const string & file_name, string nation);

 
/**
 * reads in all the txt files and gets the IATA and airport names.
 * 
 * @param file_name
 * 
 * @return returns a vector of pair with ids and pair of IATA and airport names.
 */
vector<pair<string, pair<int, int> > >recordAll(const string & file_name);

/**
 * reads the routes and gets the source IATA and destination IATA
 * 
 * @param file_name
 * @param countries
 * 
 * @return returns a vector of pairs with wanted sources and destinations.
 */
vector<pair<string, string> > recordRoutes(const string & file_name, vector<pair<string, pair<int, int> > > countries);