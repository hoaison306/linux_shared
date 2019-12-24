/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : The data structure library for Assignment 1
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "dbLib.h"

/* TODO: You can implement methods, functions that support your data structures here.
 * */
void LoadCity(TDataset *&dataSet) {
	fstream fin;
	string line;

	//doc file cities.csv: lay id, name
	fin.open("cities.csv", ios::in);
	getline(fin, line);
	while (getline(fin, line)) {
		if (line != "") {
			size_t firstPos = line.find(',');
			size_t secondPos = line.find(',', firstPos + 1);
			TCity tempCity;
			tempCity.id = stoi(line.substr(0, firstPos));
			tempCity.name = line.substr(firstPos + 1, secondPos - firstPos - 1);
			dataSet->dataCity.push_back(tempCity);
		}
	}
	fin.close();
}
void LoadLines(TDataset*& dataSet) {
	fstream fin;
	string line;
	//doc file lines.csv: lay id, city_id, name
	fin.open("lines.csv", ios::in);
	getline(fin, line);
	while (getline(fin, line)) {
		if (line != "") {
			size_t firstPos = line.find(',');
			size_t secondPos = line.find(',', firstPos + 1);
			size_t thirdPos = line.find(',', secondPos + 1);
			TLine tempLine;
			tempLine.id = stoi(line.substr(0, firstPos));
			tempLine.city_id = stoi(line.substr(firstPos + 1, secondPos - firstPos - 1));
			tempLine.name = line.substr(secondPos + 1, thirdPos - secondPos - 1);
			dataSet->dataLine.push_back(tempLine);
		}
	}
	fin.close();
}
void LoadTracks(TDataset*& dataSet) {
	fstream fin;
	string line;
	//doc file track.csv: lay id, geometry, city_id
	fin.open("tracks.csv", ios::in);
	getline(fin, line);
	while (getline(fin, line)) {
		if (line != "") {
			//tim LINESTRING
			size_t firstPos = line.find('"');	//tim dau " dau tien
			size_t secondPos = line.find('"', firstPos + 1); //tim dau " thu 2
			string geometrytemp = line.substr(firstPos + 12, secondPos - firstPos - 13);

			TTrack tempTrack;
			tempTrack.id = stoi(line.substr(0, firstPos - 1));
			tempTrack.geometry = geometrytemp;
			tempTrack.city_id = stoi(line.substr(line.find_last_of(',') + 1, line.size() - line.find_last_of(',') - 1));
			dataSet->dataTrack.push_back(tempTrack);
		}
	}
	fin.close();
}
void LoadStations(TDataset*& dataSet) {
	fstream fin;
	string line;
	//doc file station: lay het
	fin.open("stations.csv", ios::in);
	getline(fin, line);
	while (getline(fin, line)) {
		if (line != "") {
			string firsthalf = line.substr(0, line.find("POINT") - 1);
			size_t firstPos = line.find('(', line.find("POINT"));	//tim dau (
			size_t secondPos = line.find(')', line.find("POINT")); //tim dau )
			string secondhalf = line.substr(secondPos + 2, line.size() - secondPos - 2);

			TStation tempStation;
			tempStation.id = stoi(firsthalf.substr(0, firsthalf.find(',')));
			tempStation.name = firsthalf.substr(firsthalf.find(',') + 1, firsthalf.size() - firsthalf.find(',') - 1);
			tempStation.geometry = line.substr(firstPos + 1, secondPos - firstPos - 1);
			/*stringstream ss;
			ss << secondhalf;
			string word;*/
			/*getline(ss, word, ','); tempStation.buildstart = (word == "") ? 0 : stoi(word);stoi
			getline(ss, word, ','); tempStation.opening = (word == "") ? 0 : stoi(word);
			getline(ss, word, ',');	tempStation.closure = (word == "") ? 0 : stoi(word);*/
			//getline(ss, word, ',');
			string word = line.substr(line.find_last_of(',') + 1, line.size() - line.find_last_of(',') - 1);
			tempStation.city_id = (word == "") ? 0 : stoi(line.substr(line.find_last_of(',') + 1, line.size() - line.find_last_of(',') - 1));
			dataSet->dataStation.push_back(tempStation);
		}
	}
	fin.close();
}
void LoadStation_Lines(TDataset*& dataSet) {
	fstream fin;
	string line;
	//doc file station_line
	fin.open("station_lines.csv", ios::in);
	getline(fin, line);
	while (getline(fin, line)) {
		if (line != "") {
			size_t first = line.find(',');
			size_t second = line.find(',', first + 1);
			size_t third = line.find(',', second + 1);
			size_t fourth = line.find(',', third + 1);
			string temp = line.substr(0, fourth);
			stringstream ss;
			ss << temp;
			string word;
			TStation_Line tempStation_Line;
			getline(ss, word, ',');	tempStation_Line.id = (word == "") ? 0 : stoi(word);
			getline(ss, word, ','); tempStation_Line.station_id = (word == "") ? 0 : stoi(word);
			getline(ss, word, ','); tempStation_Line.line_id = (word == "") ? 0 : stoi(word);
			getline(ss, word, ','); tempStation_Line.city_id = (word == "") ? 0 : stoi(word);
			dataSet->dataStation_Line.push_back(tempStation_Line);
		}
	}
	fin.close();
}
void LoadData(void*& pData) {
	TDataset *dataSet = new TDataset;
	LoadCity(dataSet);
	LoadLines(dataSet);
	LoadTracks(dataSet);
	LoadStations(dataSet);
	LoadStation_Lines(dataSet);
	pData = dataSet;
}
bool isEqualTCity_name(const TCity& data1, const TCity& data2) {
	return data1.name == data2.name;
}
bool isEqualTCity_id(const TCity& data1, const TCity& data2) {
	return data1.id == data2.id;
}
bool isEqualTLine_id(const TLine& data1, const TLine& data2) {
	return data1.id == data2.id;
}
bool isEqualTLine_cityid(const TLine& data1, const TLine& data2) {
	return data1.city_id == data2.city_id;
}
bool isEqualTStation_cityid(const TStation& data1, const TStation& data2) {
	return data1.city_id == data2.city_id;
}
bool isEqualTStation_name(const TStation& data1, const TStation& data2) {
	return data1.name == data2.name;
}
bool isEqualTStation_id(const TStation& data1, const TStation& data2) {
	return data1.id == data2.id;
}
bool isEqualTStationLine_lineid(const TStation_Line& data1, const TStation_Line& data2) {
	return data1.line_id == data2.line_id;
}
bool isEqualTStationLine_stationid(const TStation_Line& data1, const TStation_Line& data2) {
	return data1.station_id == data2.station_id;
}
bool isEqualTTrack_id(const TTrack& data1, const TTrack& data2) {
	return data1.id == data2.id;
}
bool compareStation_id(const TStation& data1, const TStation& data2) {
	return data2.id > data1.id;
}
bool compareStID_LineID(const TStation_Line& data1, const TStation_Line& data2){
	if (data1.line_id == data2.line_id) {
		return data1.station_id == data2.station_id;
	}
	else return false;
}
void ReleaseData(void*& p) {

}
