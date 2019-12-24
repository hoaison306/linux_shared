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
	string name;
};

struct TLine {
    // The structure to store line information
	int id;
	int city_id;
	string name;
};

struct TTrack {
    // The structure to store track information
	int id;
	int city_id;
	string geometry;
};

struct TStation {
	int id;
	string name;
	string geometry;
	/*int buildstart;
	int opening;
	int closure;*/
	int city_id;
};

struct TStation_Line {
	int id;
	int station_id;
	int line_id;
	int city_id;
};

struct TTrack_Line {
	int id;
	int section_id;
	int line_id;
	int city_id;
};

class TDataset {
    // This class can be a container that help you manage your tables
	public:
		L1List<TCity> dataCity;
		L1List<TStation> dataStation;
		L1List<TLine> dataLine;
		L1List<TTrack> dataTrack;
		//L1List<TTrack_Line> dataTrack_Line;
		L1List<TStation_Line> dataStation_Line;
};

// Please add more or modify as needed
void LoadData(void* &);
void ReleaseData(void* &);
bool isEqualTCity_id(const TCity&, const TCity&);
bool isEqualTCity_name(const TCity&, const TCity&);
bool isEqualTLine_cityid(const TLine&, const TLine&);
bool isEqualTLine_id(const TLine&, const TLine&);
bool isEqualTStation_cityid(const TStation&, const TStation&);
bool isEqualTStation_name(const TStation&, const TStation&);
bool isEqualTStation_id(const TStation&, const TStation&);
bool isEqualTStationLine_lineid(const TStation_Line&, const TStation_Line&);
bool isEqualTStationLine_stationid(const TStation_Line&, const TStation_Line&);
bool isEqualTTrack_id(const TTrack&, const TTrack&);
bool compareStation_id(const TStation&, const TStation&);
bool compareStID_LineID(const TStation_Line&, const TStation_Line&);
#endif //DSA191_A1_DBLIB_H
