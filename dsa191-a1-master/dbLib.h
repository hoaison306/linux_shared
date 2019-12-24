/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#ifndef DSA191_A1_DBLIB_H
#define DSA191_A1_DBLIB_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */
struct City {
    // The structure to store city information
	int id;
	string name;
	
};

struct Line {
    // The structure to store line information
	int id;
	int city_id;
	string name;
	

};

struct Station_line {
	int id;
	int city_id, station_id, line_id;

};

struct Station {
	int id;
	string name;
	string geometry;
	int buildStart;
	int opening;
	int closure;
	int city_id;
};


struct System {
	int id;
	int city_id;
	string name;
};



struct Track {
	int id;
	string geometry;
	int city_id;
};

class Dataset {
    // This class can be a container that help you manage your tables
public:
	L1List<City> *city;
	L1List<Line> *line;
	L1List<Station_line> *stationLine;
	L1List<Station> *station;
	L1List<Track> *track;

};


// Please add more or modify as needed

void LoadData(void* &);
void ReleaseData(void* &);

bool p_idx_name(City & s1, string & s2);
bool p_idx_id(Line & id1, int & id2);
bool station_cityID(Station & st1, int &st2);
bool line_city_id(Line &l1, int& l2);
bool stationLine_line_id(Station_line &sl1, int& sl2);
bool station_name(Station &s1, string &s2);
bool station_id(Station &s1, int &s2);
bool track_id(Track &t1, int &t2);
bool station_id_bt(Station &s1, Station &s2);
bool stationLine_station_id(Station_line &s1, int &s2);
bool track_cityid(Track &t1, int &t2);
#endif //DSA191_A1_DBLIB_H
