/* Created by Nguyen Duc Dung on 2019-09-03.
 * =========================================================================================
 * Name        : processData.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - HCMUT
 * Description : Implementation of main features in the assignment
 * Course      : Data Structure and Algorithms - Fall 2019
 * =========================================================================================
 */

#include "processData.h"
#include "dsaLib.h"
#include "dbLib.h"
/* TODO: You can implement methods, functions that support your data structures here.
 * */
using namespace std;
void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
	
}

void Finalization() {
    // Release your data before exiting
	
}
/*
Confusing points:
	# Case sensitive with string input
	# 2 London city
	# csv description format of US request
	# LINESTRING of tracks.csv
	  --> In US request, update the geometry of station in tracks or not
	# Index of ISL
	# Output of a integer-array-output request type when output is none
*/
bool isNumeric(std::string str);
void CL_request(TDataset *, void *&, int &);
void CL_request(TDataset *, void *&, int &, std::string);
void LSC_request(TDataset *, void *&, int &, std::string);
void LLC_request(TDataset *, void *&, int &, std::string);
void LSL_request(TDataset *, void *&, int &, int);
void FC_request(TDataset *, void *&, int &, std::string);
void FS_request(TDataset *, void *&, int &, std::string);
void SLP_request(TDataset *, void *&, int &, int, int);
void IS_request(TDataset *, void *&, int &, std::string);
void RS_request(TDataset *, void *&, int &, int); 
void US_request(TDataset *, void *&, int &, int, std::string); 
void ISL_request(TDataset *, void *&, int &, int, int, int);
void RSL_request(TDataset *, void *&, int &, int, int);
void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
    // TODO: Implement this function for processing a request
    // NOTE: You can add other functions to support this main process.
    //       pData is a pointer to a data structure that manages the dataset
    //       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
    //       N is the size of output, must be a non-negative number
	stringstream str(pRequest);
	std::string requestType, parameter, parameter2, parameter3;
	int para1, para2, para3;
	getline(str, requestType, ' ');
	if (requestType == "CL") {
		getline(str, parameter, '\n');
		if (parameter == "")
			CL_request((TDataset*)pData, pOutput, N);
		else
			CL_request((TDataset*)pData, pOutput, N, parameter);
	}
	else if (requestType == "LSC") {
		getline(str, parameter, '\n');
		if (parameter == "")
			pOutput = nullptr;
		else
			LSC_request((TDataset*)pData, pOutput, N, parameter);
	}
	else if (requestType == "LLC") {
		getline(str, parameter, '\n');
		if (parameter == "")
			pOutput = nullptr;
		else
			LLC_request((TDataset*)pData, pOutput, N, parameter);
	}
	else if (requestType == "LSL") {
		getline(str, parameter, '\n');
		if (!isNumeric(parameter))
			pOutput = nullptr;
		else {
			LSL_request((TDataset*)pData, pOutput, N, std::stoi(parameter));
		}
	}
	else if (requestType == "FC") {
		getline(str, parameter, '\n');
		if (parameter == "")
			pOutput = nullptr;
		else
			FC_request((TDataset*)pData, pOutput, N, parameter);
	}
	else if (requestType == "FS") {
		getline(str, parameter, '\n');
		if (parameter == "")
			pOutput = nullptr;
		else
			FS_request((TDataset*)pData, pOutput, N, parameter);
	}
	else if (requestType == "SLP") {
		getline(str, parameter, ' ');
		getline(str, parameter2, '\n');
		if (isNumeric(parameter) && isNumeric(parameter2)) {
			para1 = std::stoi(parameter);
			para2 = std::stoi(parameter2);
			SLP_request((TDataset*)pData, pOutput, N, para1, para2);
		}
		else
			pOutput = nullptr;
	}
	else if (requestType == "IS") {
		getline(str, parameter, '\n');
		if (parameter == "")
			pOutput = nullptr;
		else
			IS_request((TDataset*)pData, pOutput, N, parameter);
	}
	else if (requestType == "RS") {
		getline(str, parameter, '\n');
		if (isNumeric(parameter))
			RS_request((TDataset*)pData, pOutput, N, std::stoi(parameter));
		else
			pOutput = nullptr;
	}
	else if (requestType == "US") {
		getline(str, parameter, ' ');
		if (!isNumeric(parameter))
			pOutput = nullptr;
		else {
			para1 = std::stoi(parameter);
			getline(str, parameter2, '\n');
			US_request((TDataset*)pData, pOutput, N, para1, parameter2);
		}
	}
	else if (requestType == "ISL") {
		getline(str, parameter, ' ');
		getline(str, parameter2, ' ');
		getline(str, parameter3, '\n');
		if (!isNumeric(parameter) || !isNumeric(parameter2) || !isNumeric(parameter3))
			pOutput = nullptr;
		else if (std::stoi(parameter3) > ((TDataset*)pData)->station_line.getSize() || std::stoi(parameter) < 0 || std::stoi(parameter2) < 0 || std::stoi(parameter3) < 0)
			pOutput = nullptr;
		else
			ISL_request((TDataset*)pData, pOutput, N, std::stoi(parameter), std::stoi(parameter2), std::stoi(parameter3));
	}
	else if (requestType == "RSL") {
		getline(str, parameter, ' ');
		getline(str, parameter2, '\n');
		if (!isNumeric(parameter) || !isNumeric(parameter2))
			pOutput = nullptr;
		else
			RSL_request((TDataset*)pData, pOutput, N, std::stoi(parameter), std::stoi(parameter2));
	}
	else {
		pOutput = nullptr;
	}
}

template<typename T>
void listToArray(T &a, T *& arr) {
	arr[0] = a;
	arr++;
}

bool compareString(std::string str1, std::string str2) {
	if (str1.length() != str2.length())
		return false;
	for (int i = 0; i < str1.length(); i++) {
		if (tolower(str1[i]) != tolower(str2[i]))
			return false;
	}
	return true;
}
bool TCity_compareName(const TCity &city1, const TCity &city2) {
	return (compareString(city1.name, city2.name) || compareString(city1.url_name, city2.url_name));
}
bool isNumeric(std::string str) {
	if (str == "")
		return false;
	for (char c : str)
		if (c < '0' || c > '9')
			return false;
	return true;
}
bool TStationLine_compareStationID(const TStation_Line& sl1, const TStation_Line& sl2) {
	return sl1.station_id == sl2.station_id;
}
bool TStationLine_compareLineID(const TStation_Line &st1, const TStation_Line&st2) {
	return st1.line_id == st2.line_id;
}
bool TStationLine_compare(const TStation_Line &st1, const TStation_Line&st2) {
	if (st1.line_id == st2.line_id)
		return TStationLine_compareStationID(st1, st2);
	else
		return false;
}
bool TStation_compareName(const TStation &station1, const TStation &station2) {
	return compareString(station1.name, station2.name);
}
bool TStation_compareID(const TStation &st1, const TStation &st2) {
	return st1.id == st2.id;
}
bool TStation_compareCityID(const TStation &st1, const TStation &st2) {
	return st1.city_id == st2.city_id;
}
void TStation_getID(L1List<int> *&list, TStation &st) {
	list->push_back(st.id);
}
void TStation_IDfromIndex(const TStation &st, int*&arr) {
	arr[0] = st.id;
	arr++;
}
void TStation_updateStation(TStation &oldInfo, TStation &newInfo) {
	// A sign for successfully find a station
	newInfo.id = 0;
	if (newInfo.name != "")
		oldInfo.name = newInfo.name;
	if (newInfo.geometry != "")
		oldInfo.geometry = newInfo.geometry;
	if (newInfo.city_id != -1)
		oldInfo.city_id = newInfo.city_id;
}
bool TTrack_compareID(const TTrack &t1, const TTrack &t2) {
	return t1.id == t2.id;
}
bool TTrack_findCoordinate(const TTrack &track, const TTrack &station) {
	stringstream s(station.geometry);
	std::string stationGeo;
	getline(s, stationGeo, ',');
	if (track.geometry.find(stationGeo) == std::string::npos)
		return false;
	else
		return true;
}
void TTrack_deleteStation(TTrack &track, TTrack &station) {
	int pos = track.geometry.find(station.geometry);
	track.geometry.erase(pos, station.geometry.length());
	if (pos == 0 && track.geometry[pos] == ',')
		track.geometry.erase(pos, 1);
	// Prevent out of bound exception
	if (pos != 0 && track.geometry[pos - 1] == ',')
		track.geometry.erase(pos - 1, 1);
}
void TTrack_updateStation(TTrack &track, TTrack &station) {
	stringstream str(station.geometry);
	std::string oldCoordinate, newCoordinate;
	getline(str, oldCoordinate, ',');
	getline(str, newCoordinate, '\n');
	int startPos = track.geometry.find(oldCoordinate);
	track.geometry.replace(startPos, oldCoordinate.length(), newCoordinate);
	// For testing
	/*std::cout << "New track look like:\n";
	std::cout << track.geometry;*/
}
// Bug-free
void CL_request(TDataset *pData, void * &pOutput, int &N) {
	// Count the number of lines in the dataset.
	N = 1;
	pOutput = new int[1];
	((int*)pOutput)[0] = pData->lines.getSize();
}
// # Case sensitive
// # 2 London city
void CL_request(TDataset *pData, void *& pOutput, int &N, std::string inputCityName) {
	// Count the number of lines in the given city. If the city does not exist, return -1.
	int numberOfLines = 0;
	N = 1;
	// Get city id from city name
	int cityID = -1;
	TCity temp;
	temp.name = inputCityName;
	temp.url_name = inputCityName;
	bool(*pTraverseFunc)(const TCity&, const TCity&);
	pTraverseFunc = TCity_compareName;
	int index = pData->city.findIndex(pTraverseFunc, temp);

	pOutput = new int[1];
	if (index == -1) {
		((int*)pOutput)[0] = -1;
		return;
	}
	else
		cityID = pData->city[index].id;
	for (int i = 0; i < pData->lines.getSize(); i++) {
		if (pData->lines[i].city_id == cityID)
			numberOfLines++;
	}
	((int*)pOutput)[0] = numberOfLines;
}
// # Case sensitive
void LSC_request(TDataset *pData, void *& pOutput, int &N, std::string inputCityName) {
	int cityID = -1;
	TCity temp;
	temp.name = inputCityName;
	temp.url_name = inputCityName;
	bool(*pTCity_compareName)(const TCity&, const TCity&);
	pTCity_compareName = TCity_compareName;
	int index = pData->city.findIndex(pTCity_compareName, temp);
	
	if (index == -1) {
		pOutput = new int[1];
		((int*)pOutput)[0] = -1;
		N = 1;
		return;
	}
	else
		cityID = pData->city[index].id;
	// Find list of stations ID
	TStation tempStation;
	tempStation.city_id = cityID;
	bool(*pTStation_compareCityID)(const TStation&, const TStation&);
	pTStation_compareCityID = &TStation_compareCityID;
	void(*pTStation_getID)(L1List<int> *&, TStation &);
	pTStation_getID = &TStation_getID;
	L1List<int> *listOfStationsID = pData->station.findListOfValues(pTStation_compareCityID, pTStation_getID, tempStation);
	
	// Move result from list to output array
	void(*pListToArray)(int &a, int *& arr);
	pListToArray = &listToArray<int>;
	N = listOfStationsID->getSize();
	pOutput = new int[N];
	int *outputArr = &((int*)pOutput)[0];
	listOfStationsID->traverseAndOperate(pListToArray, outputArr);
}
// # Case sensitive
void LLC_request(TDataset *pData, void *& pOutput, int &N, std::string inputCityName) {
	// List lines (line_id) of a city (given <city_name>). The order of this list is given in lines.csv.
	int cityID = -1;
	TCity temp;
	temp.name = inputCityName;
	temp.url_name = inputCityName;
	bool(*pTraverseFunc)(const TCity&, const TCity&);
	pTraverseFunc = TCity_compareName;
	int index = pData->city.findIndex(pTraverseFunc, temp);

	if (index == -1) {
		pOutput = new int[1];
		((int*)pOutput)[0] = -1;
		N = 1;
		return;
	}
	else
		cityID = pData->city[index].id;

	L1List<int> listOfLines;
	for (int i = 0; i < pData->lines.getSize(); i++) {
		if (pData->lines[i].city_id == cityID) {
			listOfLines.push_back(pData->lines[i].id);
		}
	}
	N = listOfLines.getSize();
	pOutput = new int[N];
	// Move the list of result to an array 
	void(*pFunc)(int& a, int*& arr);
	pFunc = &listToArray<int>;
	int *pTraverse = (int*)pOutput;
	listOfLines.traverseAndOperate(pFunc, pTraverse);
}

void LSL_request(TDataset *pData, void *& pOutput, int &N, int lineID) {
	// List stations (station_id) of a line with <line_id>.
	// The order of station is determined by its appearance in station_lines.csv.
	TStation_Line tempSL;
	tempSL.line_id = lineID;
	bool(*pCompareFunc)(const TStation_Line&, const TStation_Line&);
	pCompareFunc = &TStationLine_compareLineID;
	L1List<int> *listOfIndexes = pData->station_line.findListOfIndexes(pCompareFunc, tempSL);
	N = listOfIndexes->getSize();
	pOutput = new int[N];
	for (int i = 0; i < N; i++) {
		((int*)pOutput)[i] = pData->station_line[(*listOfIndexes)[i]].station_id;
	}
}
// # Case sensitive
void FC_request(TDataset *pData, void *& pOutput, int &N, std::string inputCityName) {
	// Find a city with the given name. Return the first city_id if found, -1 otherwise.
	N = 1;
	pOutput = new int[1];
	TCity temp;
	temp.name = inputCityName;
	temp.url_name = inputCityName;
	bool(*pTraverseFunc)(const TCity&, const TCity&);
	pTraverseFunc = TCity_compareName;
	int index = pData->city.findIndex(pTraverseFunc, temp);

	if (index == -1) {
		((int*)pOutput)[0] = -1;
		return;
	}
	else {
		((int*)pOutput)[0] = pData->city[index].id;
	}
}
// # Case sensitive
void FS_request(TDataset *pData, void *& pOutput, int &N, std::string stationName) {
	// Find a station with the given name. Return the first station_id if found, -1 otherwise.
	N = 1;
	pOutput = new int[1];
	bool(*pTraverseFunc)(const TStation&, const TStation&);
	pTraverseFunc = &TStation_compareName;
	TStation temp;
	temp.name = stationName;

	int index = pData->station.findIndex(pTraverseFunc, temp);
	if (index == -1)
		((int*)pOutput)[0] = -1;
	else
		((int*)pOutput)[0] = pData->station[index].id;
}
// # LINESTRING
void SLP_request(TDataset *pData, void *& pOutput, int &N, int stationID, int trackID) {
	/*
	Find the position of a station in a track.
	Return the index of that station if found, -1 otherwise.
	The order of station is determined by LINESTRING in tracks.csv.
	*/
	std::string coordinate = "";
	N = 1;
	pOutput = new int[1];
	TStation temp;
	temp.id = stationID;
	bool(*pTraverFunc)(const TStation&, const TStation&);
	pTraverFunc = &TStation_compareID;
	int stationIdx = -1;
	int index = pData->station.findIndex(pTraverFunc, temp);
	// Find the coordinate of station
	/*for (int i = 0; i < pData->station.getSize(); i++) {
		if (pData->station[i].id == stationID) {
			coordinate = pData->station[i].geometry;
			break;
		}
	}*/
	if (index == -1) {
		((int*)pOutput)[0] = -1;
		return;
	}
	else
		coordinate = pData->station[index].geometry;
	// Find its coordinate in LINESTRING
	bool(*pTraverseFunc2)(const TTrack&, const TTrack&);
	pTraverseFunc2 = &TTrack_compareID;
	TTrack tempTrack;
	tempTrack.id = trackID;
	int trackIndex = pData->track.findIndex(pTraverseFunc2, tempTrack);
	if (trackIndex == -1) {
		((int*)pOutput)[0] = -1;
		return;
	}
	int pos;
	std::string linestring = pData->track[trackIndex].geometry;
	if (linestring.find(coordinate) == std::string::npos) {
		((int*)pOutput)[0] = -1;
		return;
	}
	else {

		pos = linestring.find(coordinate);
		int searchBeginPos = 0;
		stationIdx = 0;
		while ((searchBeginPos = linestring.find(',', searchBeginPos)) <= pos && searchBeginPos != std::string::npos) {
			stationIdx++;
			searchBeginPos++;
		}
		((int*)pOutput)[0] = stationIdx;
		return;
	}
	
	/*for (int i = 0; i < pData->track.getSize(); i++) {
		if (pData->track[i].id == trackID) {
			std::string linestring = pData->track[i].geometry;
			
		}
	}*/
	if (stationIdx == -1) {
		((int*)pOutput)[0] = stationIdx;
	}
}

void IS_request(TDataset *pData, void *& pOutput, int &N, std::string csv_description) {
	/*
	Insert a station into the dataset
	If this operation success, we have to receive station id as the return value
	The allocated id should be the id_max + 1
	*/
	N = 1;
	pOutput = new int[1];
	std::string aStr = csv_description;
	stringstream stream(csv_description);
	std::string col;
	std::string emptyStr = "";
	L1List<std::string> listOfCol;
	while (getline(stream, col, ',')) {
		listOfCol.push_back(col);
	}
	if (csv_description[csv_description.length() - 1] == ',')
		listOfCol.push_back(emptyStr);
	if (listOfCol.getSize() != 5 || listOfCol[1].find("POINT(") == std::string::npos || listOfCol[1].find(")") == std::string::npos) {
		((int*)pOutput)[0] = -1;
		return;
	}
	TStation temp;
	temp.id = pData->max_station_id + 1;
	++(pData->max_station_id);
	temp.name = listOfCol[0];
	
	if (listOfCol[1] != "")
		listOfCol[1] = listOfCol[1].substr(listOfCol[1].find('(') + 1, listOfCol[1].length() - 2 - listOfCol[1].find('('));
	// For debugging
	std::string geo = listOfCol[1];
	temp.geometry = listOfCol[1];
	temp.city_id = -1;
	// Find city_id, may be not necessary
	/*for (int i = 0; i < pData->track.getSize(); i++) {
		if (pData->track[i].geometry.find(geo) != std::string::npos) {
			temp.city_id = pData->track[i].city_id;
			break;
		}
	}*/
	//
	pData->station.push_back(temp);
	
	((int*)pOutput)[0] = temp.id;
}

void RS_request(TDataset *pData, void *&pOutput, int &N, int stationID) {
	//int stationIdx = 0;

	// Delete from stations
	std::string stationGeo = "";
	N = 1;
	pOutput = new int[1];
	TStation temp;
	temp.id = stationID;
	bool(*pTraverFunc)(const TStation&, const TStation&);
	pTraverFunc = &TStation_compareID;
	int stationIdx = -1;
	int index = pData->station.findIndex(pTraverFunc, temp);
	if (index == -1) {
		((int*)pOutput)[0] = -1;
		return;
	}
	((int*)pOutput)[0] = 0;
	stationGeo = pData->station[index].geometry;
	if (stationID == pData->max_station_id)
		--pData->max_station_id;
	pData->station.remove(index);
	// Delete from station_lines
	TStation_Line tempSL;
	tempSL.station_id = stationID;
	bool(*pTraverseFunc2)(const TStation_Line&, const TStation_Line&);
	pTraverseFunc2 = &TStationLine_compareStationID;
	L1List<int> *listOfStations = pData->station_line.findListOfIndexes(pTraverseFunc2, tempSL);
		
	listOfStations->reverse(); // Delete from the tail of list 
	for (int i = 0; i < listOfStations->getSize(); i++)
		pData->station_line.remove((*listOfStations)[i]);
	// Delete from tracks
	bool(*pTTrack_findCoordinate)(const TTrack &, const TTrack &);
	pTTrack_findCoordinate = &TTrack_findCoordinate;
	void(*pDeleteStationFromTrack)(TTrack &, TTrack &);
	pDeleteStationFromTrack = &TTrack_deleteStation;
	TTrack tempTrack;
	tempTrack.geometry = stationGeo;
	pData->track.compareAndOperate(pTTrack_findCoordinate, pDeleteStationFromTrack, tempTrack);
}
// # csv_description format and id updating
// # update the coordinate in LINESTRING
void US_request(TDataset *pData, void *& pOutput, int &N, int stationID, std::string csv_description) {
	int numOfCol = 0, pos = 0;
	N = 1;
	pOutput = new int[1];
	// Find number of columns in csv description
	while (csv_description.find(',', pos) != std::string::npos) {
		pos = csv_description.find(',', pos) + 1;
		numOfCol++;
	}
	numOfCol++;
	// Confusing
	// csv description is not in right format
	// Assume that there is no id column
	if (numOfCol != 6) {
		((int*)pOutput)[0] = -1;
		return;
	}
	stringstream str(csv_description);
	std::string col;
	L1List<std::string> listOfCol;
	while (getline(str, col, ','))
		listOfCol.push_back(col);
	// the case when the last col is empty
	col = "";
	if (listOfCol.getSize() < numOfCol)
		listOfCol.push_back(col);
	// name,geometry,buildstart,opening,closure,city_id
	TStation tempStation;
	tempStation.name = listOfCol[0];
	if (listOfCol[1] != "" && listOfCol[1].find("POINT(") != std::string::npos && listOfCol[1].find(')') != std::string::npos) {
		listOfCol[1] = listOfCol[1].substr(listOfCol[1].find('(') + 1, listOfCol[1].length() - 2 - listOfCol[1].find('('));
		tempStation.geometry = listOfCol[1];
	}
	else
		tempStation.geometry = "";
	if (isNumeric(listOfCol[5]))
		tempStation.city_id = std::stoi(listOfCol[5]);
	else
			tempStation.city_id = -1;
	tempStation.id = stationID;
	bool(*pTStation_compareID)(const TStation &, const TStation &);
	pTStation_compareID = &TStation_compareID;
	void(*pTStation_updateStation)(TStation &, TStation &);
	pTStation_updateStation = &TStation_updateStation;
	// Get current coordinate before update stations.csv
	int index = pData->station.findIndex(pTStation_compareID, tempStation);
	std::string oldStationGeo = pData->station[index].geometry;
	// Update station in stations.csv
	pData->station.compareAndOperate(pTStation_compareID, pTStation_updateStation, tempStation);
	N = 1;
	pOutput = new int[1];
	if (tempStation.id == 0)
		((int*)pOutput)[0] = tempStation.id;
	else {
		((int*)pOutput)[0] = -1;
		return;
	}
	// Update coordinate in LINESTRING
	if (tempStation.geometry != "") {
		TTrack newStationGeo;
		// geometry of the temp struct var comprise of the old and new coordinate: "old_coordinate,new_coordinate"
		newStationGeo.geometry = oldStationGeo + ',' + tempStation.geometry;
		bool(*pTTrack_findCoordinate)(const TTrack&, const TTrack&);
		pTTrack_findCoordinate = &TTrack_findCoordinate;
		void(*pTTrack_updateStation)(TTrack&, TTrack&);
		pTTrack_updateStation = &TTrack_updateStation;
		pData->track.compareAndOperate(pTTrack_findCoordinate, pTTrack_updateStation, newStationGeo);
	}
	//
	

}

void ISL_request(TDataset *pData, void *&pOutput, int &N, int stationID, int lineID, int idx)
{
	// Find if the stationID is already in the line
	N = 1;
	pOutput = new int[1];
	bool(*pTStationLine_compare)(const TStation_Line&, const TStation_Line&);
	pTStationLine_compare = &TStationLine_compare;
	TStation_Line tempSL;
	tempSL.station_id = stationID;
	tempSL.line_id = lineID;
	int isStationInLine = pData->station_line.findIndex(pTStationLine_compare, tempSL);
	if (isStationInLine != -1) {
		((int*)pOutput)[0] = -1;
		return;
	}
	// 
	pTStationLine_compare = &TStationLine_compareLineID;
	L1List<int> *idxOfStationInLine = pData->station_line.findListOfIndexes(pTStationLine_compare, tempSL);
	if (idx > idxOfStationInLine->getSize()) {
		((int*)pOutput)[0] = -1;
	}
	// Confusing
	else if (idx == idxOfStationInLine->getSize()) {
		pData->station_line.insert((*idxOfStationInLine)[idx-1] + 1, tempSL);
		((int*)pOutput)[0] = 0;
	}
	else {
		pData->station_line.insert((*idxOfStationInLine)[idx], tempSL);
		((int*)pOutput)[0] = 0;
	}
}

void RSL_request(TDataset *pData, void *&pOutput, int &N, int stationID, int lineID)
{
	N = 1;
	pOutput = new int[1];
	bool(*pTStationLine_compare)(const TStation_Line&, const TStation_Line&);
	pTStationLine_compare = &TStationLine_compare;
	TStation_Line tempSL;
	tempSL.station_id = stationID;
	tempSL.line_id = lineID;
	int index = pData->station_line.findIndex(pTStationLine_compare, tempSL);
	if (index == -1) {
		((int*)pOutput)[0] = -1;
		
	}
	else {
		pData->station_line.remove(index);
		((int*)pOutput)[0] = 0;
	}
}
