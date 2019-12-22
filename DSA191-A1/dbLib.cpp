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


void LoadData(void *&pData) {
	TDataset *dataContainer = new TDataset;
	//pData = (TDataset*)pData;
	pData = dataContainer;
	loadCityData(dataContainer->city);
	loadStationData(dataContainer->station, dataContainer->max_station_id);
	loadLineData(dataContainer->lines);
	loadTrackData(dataContainer->track);
	loadStationLineData(dataContainer->station_line);
	/*for (int i = 0; i < ((TDataset*)pData)->city.getSize(); i++) {
		std::cout << ((TDataset*)pData)->city[i].id << ','
			<< ((TDataset*)pData)->city[i].name << ','
			<< ((TDataset*)pData)->city[i].url_name << '\n';
	}*/

}
void ReleaseData(void* &pData) {
	delete pData;
}
// Done
void loadCityData(L1List<TCity> &cities) {
	fstream fin;
	fin.open("cities.csv", ios::in);
	std::string line, ele, a = "";
	L1List<std::string> col;
	int numOfCol = 0, pos = 0;
	// Find number of columns in file
	getline(fin, line);
	while (line.find(',', pos) != std::string::npos) {
		pos = line.find(',', pos) + 1;
		numOfCol++;
	}
	numOfCol++;
	// Start reading
	while (getline(fin, line)) {
		stringstream str(line);
		col.clean();
		while (getline(str, ele, ',')) {
			col.push_back(ele);
		}
		if (col.getSize() < numOfCol)
			col.push_back(a);

		// 
		TCity temp;
		temp.id = std::stoi(col[0]);
		temp.name = col[1];
		temp.url_name = col[4];
		//temp.country = col[5];
		cities.push_back(temp);
	}
	fin.close();
}
// Done
void loadStationData(L1List<TStation> &station, int &max_station_id) {
	max_station_id = 0;
	fstream fin;
	fin.open("stations.csv", ios::in);
	std::string line, ele, a = "", stationName;
	L1List<std::string> listOfCol;
	int numOfCol = 0, pos = 0;
	// Find number of columns in file
	getline(fin, line);
	while (line.find(',', pos) != std::string::npos) {
		pos = line.find(',', pos) + 1;
		numOfCol++;
	}
	numOfCol++;
	// Start reading
	while (getline(fin, line)) {
		stationName = "";
		if (line.find("\"") != std::string::npos) {
			int start = line.find("\"");
			int end = line.find("\"", start + 1);
			stationName = line.substr(start + 1, end - start - 1);
			line.erase(start + 1, end - start - 1);
		}
		stringstream str(line);
		listOfCol.clean();
		while (getline(str, ele, ',')) {
			listOfCol.push_back(ele);
		}
		if (listOfCol.getSize() < numOfCol)
			listOfCol.push_back(a);
		TStation temp;
		if (listOfCol[2] != "")
			listOfCol[2] = listOfCol[2].substr(listOfCol[2].find('(') + 1, listOfCol[2].length() - 2 - listOfCol[2].find('('));
		//std::cout << col[2] << '\n';
		//if (col[0] != " ")
		temp.id = (listOfCol[0] != "") ? std::stoi(listOfCol[0]) : -1;
		if (temp.id > max_station_id)
			max_station_id = temp.id;
		temp.name = (stationName == "") ? listOfCol[1] : stationName;
		temp.geometry = listOfCol[2];
		temp.city_id = (listOfCol[6] != "") ? std::stoi(listOfCol[6]) : -1;
		station.push_back(temp);
	}
	fin.close();
}
// Done
void loadStationLineData(L1List<TStation_Line> &station_line) {
	fstream fin;
	std::string line, ele, a = "";
	L1List<std::string> col;
	int numOfCol = 0, pos = 0;
	fin.open("station_lines.csv", ios::in);
	// Find number of columns in file
	getline(fin, line);
	//L1List<Station_Line> station_line;
	while (getline(fin, line)) {
		stringstream str(line);
		col.clean();
		while (getline(str, ele, ',')) {
			col.push_back(ele);
		}
		if (col.getSize() < numOfCol)
			col.push_back(a);
		TStation_Line temp;
		temp.station_id = (col[1] != "") ? std::stoi(col[1]) : -1;
		temp.line_id = (col[2] != "") ? std::stoi(col[2]) : -1;
		station_line.push_back(temp);
	}
	fin.close();
}
// Done
void loadLineData(L1List<TLine> &lines) {
	fstream fin;
	fin.open("lines.csv", ios::in);
	std::string line, ele, a = "";
	L1List<std::string> col;
	int numOfCol = 0, pos = 0;
	// Find number of columns in file
	getline(fin, line);
	while (line.find(',', pos) != std::string::npos) {
		pos = line.find(',', pos) + 1;
		numOfCol++;
	}
	numOfCol++;
	// Start reading
	while (getline(fin, line)) {
		if (line.find("\"") != std::string::npos) {
			int start = line.find("\"");
			int end = line.find("\"", start + 1);
			line.erase(start + 1, end - start - 1);
		}
		stringstream str(line);
		col.clean();
		while (getline(str, ele, ',')) {
			col.push_back(ele);
		}
		if (col.getSize() < numOfCol)
			col.push_back(a);
		TLine temp;
		temp.id = (col[0] != "") ? std::stoi(col[0]) : -1;
		temp.city_id = (col[1] != "") ? std::stoi(col[1]) : -1;
		lines.push_back(temp);
	}
	fin.close();


}
void loadTrackData(L1List<TTrack> &track) {
	fstream fin;
	fin.open("tracks.csv", ios::in);
	std::string line, ele, a = "";
	L1List<std::string> col;
	int numOfCol = 0, pos = 0;
	// Find number of columns in file
	getline(fin, line);
	while (line.find(',', pos) != std::string::npos) {
		pos = line.find(',', pos) + 1;
		numOfCol++;
	}
	numOfCol++;
	// Start reading
	int beginLS = 0, endLS = 0;
	while (getline(fin, line)) {
		TTrack temp;
		// Get the LINESTRING field and then delete it from line
		beginLS = 0, endLS = 0;
		beginLS = line.find('"');
		endLS = line.find('"', beginLS + 1);
		temp.geometry = line.substr(beginLS + 1, endLS - beginLS - 1);
		line = line.erase(beginLS + 1, endLS - beginLS - 1);

		stringstream str(line);
		col.clean();
		while (getline(str, ele, ',')) {
			col.push_back(ele);
		}
		// Temporary fix for exception
		if (col.getSize() < 7)
			col.push_back(a);
		temp.geometry = temp.geometry.substr(temp.geometry.find('(') + 1, temp.geometry.length() - temp.geometry.find('(') - 2);
		temp.city_id = (col[col.getSize() - 1] != "") ? stoi(col[col.getSize() - 1]) : -1;
		temp.id = (col[0] != "") ? stoi(col[0]) : -1;
		track.push_back(temp);
	}
	fin.close();
}
