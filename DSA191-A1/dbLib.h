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
struct TCity {
    // The structure to store city information
	int id;
	std::string name, url_name;
};

struct TLine {
    // The structure to store line information
	int id, city_id;
	//L1List<TCity*> citiesOfLine;
	//std::string name, url_name, color;
	// 1 list of reference to stations that belong to that line
};

struct TTrack {
    // The structure to store track information
	int id, city_id;
	std::string geometry;
};
struct TStation {
	int id, city_id;
	std::string name, geometry;
};
struct TStation_Line {
	int station_id, line_id;
};
class TDataset {
    // This class can be a container that help you manage your tables
public:
	int max_station_id;
	L1List<TCity> city;
	L1List<TLine> lines;
	L1List<TTrack> track;
	L1List<TStation> station;
	L1List<TStation_Line> station_line;
};

// Please add more or modify as needed

void LoadData(void* &);
void loadCityData(L1List<TCity> &);
void loadStationData(L1List<TStation> &, int &);
void loadLineData(L1List<TLine> &);
void loadStationLineData(L1List<TStation_Line> &);
void loadTrackData(L1List<TTrack> &);
void ReleaseData(void* &);

#endif //DSA191_A1_DBLIB_H
