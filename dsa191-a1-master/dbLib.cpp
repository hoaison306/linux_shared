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
L1List<City>* readCity() {
	L1List<City>* obj=new L1List<City>();
	City temp_City;
	string tempData;
	ifstream myFile;
	int i = 0;
	myFile.open("cities.csv", ios::in);
	bool isok = 0;
	while (getline(myFile, tempData)) {
		if (i > 0) {
			if (tempData.size() != 0) {
				string get;
				stringstream s(tempData);
				getline(s, get, ',');  temp_City.id = stoi(get);
				getline(s, get, ','); temp_City.name = get;
				obj->insertHead(temp_City);
			}
			else isok = 1;
		}
		i++;
	}
	
	myFile.close();
	//if (isok ==0)
		obj->reverse();
	return obj;
}

bool p_idx_name(City & s1, string & s2) {
	return s1.name == s2;
}

L1List<Line>* readLine() {
	L1List<Line>* obj=new L1List<Line>();
	Line temp_Line;
	ifstream myFile;
	string tempData;
	int i = 0;
	myFile.open("lines.csv");
	bool isok = 0;
	while (getline(myFile, tempData)) {
		if (i > 0) {
			if (tempData.size() != 0) {
				string q, get;
				stringstream s(tempData);

				getline(s, get, ','); temp_Line.id = stoi(get);
				getline(s, get, ','); temp_Line.city_id = stoi(get);

				obj->insertHead(temp_Line);
			}
			else isok = 1;
		}
		i++;
	}
	myFile.close();
	//if(isok==0)
	obj->reverse();
	return obj;
}

bool p_idx_id(Line & id1, int & id2) {
	return id1.city_id == id2;
}

bool line_city_id(Line &l1, int& l2) {
	return l1.city_id == l2;
}

L1List<Station>* readStation() {
	L1List<Station>* obj = new L1List<Station>();
	Station temp_Station;
	ifstream myFile;
	int i = 0;
	string tempData;
	myFile.open("stations.csv");
	bool isok = 0;
	while (getline(myFile,tempData)) {
	
		if (i > 0) {
			if (tempData.size() != 0) {
				int pos = tempData.find_first_of(',');
				temp_Station.id = stoi(tempData.substr(0, pos));
				tempData.erase(0, pos + 1);
				pos = tempData.find("POINT");
				temp_Station.name = tempData.substr(0, pos - 1);
				tempData.erase(0, pos + 5);
				stringstream s(tempData);
				string get;
				/*while(getline(s, get, ',') ){
					if (key == 0) {
						temp_Station.geometry = get.substr(1, get.size() - 2);
					}
					else if (key == 1 && get.size() != 0) temp_Station.buildStart = stoi(get);
					else if (key == 2 && get.size() !=0) temp_Station.opening = stoi(get);
					else if (key == 3 && get.size() != 0) temp_Station.closure = stoi(get);
					else if (key == 4 && get.size() != 0)temp_Station.city_id = stoi(get);
					key++;
				}*/

				getline(s, get, ','); /*if (get.size() != 0)*/ temp_Station.geometry = get.substr(1, get.size() - 2);
				/*	getline(s, get, ','); if (get.size() != 0) temp_Station.buildStart = stoi(get);
					getline(s, get, ','); if (get.size() != 0) temp_Station.opening = stoi(get);
					getline(s, get, ','); if (get.size() != 0) temp_Station.closure = stoi(get);
					getline(s, get, ','); if (get.size() != 0) temp_Station.city_id = stoi(get);*/
				pos = tempData.find_last_of(',');
				temp_Station.city_id = stoi(tempData.substr(pos + 1, tempData.size() - pos - 1));
				obj->insertHead(temp_Station);
			}
			else isok = 1;
		/*	stringstream s(tempData);
			string get;
			while (getline(s, get, ',')) {
				if (key == 0) {
					temp_Station.id = stoi(get);
					tempData.erase(0, get.size() + 1);
					key++;
					break;
				}
			}
			int pos = tempData.find("POINT");
			temp_Station.name = tempData.substr(0, pos - 1);
			tempData.erase(0, pos + 6);
			stringstream qq(tempData);
			string get1;
			while (getline(qq, get1, ',')) {
				if (keyq == 0) {
					get1.erase(get1.size() - 1, 1);
					temp_Station.geometry = get1;
				}
				else if (keyq == 1 && get1.size() != 0) temp_Station.buildStart = stoi(get1);
				else if (keyq == 2 && get1.size() != 0) temp_Station.opening = stoi(get1);
				else if (keyq == 3 && get1.size() !=0) temp_Station.closure = stoi(get1);
				else if (keyq == 4 && get1.size() != 0)temp_Station.city_id = stoi(get1);
				keyq++;
			}
			obj->push_back(temp_Station);*/
			
		}
		i++;
		
	}
	myFile.close();
	//if(isok==0)
	obj->reverse();
	return obj;
}

bool station_cityID(Station & st1, int &st2) {
	return st1.city_id == st2;
}

bool station_name(Station &s1, string &s2) {
	return s1.name == s2;
}

bool station_id_bt(Station &s1, Station &s2) {
	return s1.id > s2.id;
}

bool station_id(Station &s1, int &s2) {
	return s1.id == s2;
}

L1List<Station_line>* readStation_line() {
	L1List<Station_line>* obj = new L1List<Station_line>();
	Station_line temp_Station_line;
	ifstream myFile;
	int i = 0;
	string tempData;
	myFile.open("station_lines.csv");
	bool isok = 0;
	while (getline(myFile, tempData)) {
		if (i > 0) {
			if (tempData.size() != 0) {
				string q, get;
				stringstream s(tempData);

				getline(s, get, ','); temp_Station_line.id = stoi(get);
				getline(s, get, ','); temp_Station_line.station_id = stoi(get);
				getline(s, get, ','); temp_Station_line.line_id = stoi(get);
				//getline(s, get, ','); temp_Station_line.city_id = stoi(get);
				obj->insertHead(temp_Station_line);
			}
			else isok = 1;
		}
		i++;
	}
	myFile.close();
	//if(isok==0)
	obj->reverse();
	return obj;
}

bool stationLine_line_id(Station_line &sl1, int& sl2) {
	return sl1.line_id == sl2;
}

bool stationLine_station_id(Station_line &s1, int &s2) {
	return s1.station_id == s2;
}

L1List<Track>* readTrack() {
	L1List<Track>* obj = new L1List<Track>();
	Track temp_Track;
	string tempData;
	int i = 0;
	ifstream myFile;
	myFile.open("tracks.csv");

	/* ifstream myFile("tracks.csv", ios::binary | ios::ate);
	ifstream::pos_type pos = myFile.tellg();
	myFile.seekg(0, std::ios::end);
	long length = myFile.tellg();
	myFile.seekg(0, std::ios::beg);

	char *buffer = new char[pos];
	myFile.read(buffer, length);
	string s(buffer);
	stringstream ss(s);
	delete[] buffer;
	myFile.close();*/

	bool isok = false;

	while(getline(myFile, tempData)) {
		if (i > 0) {
			stringstream q(tempData);
			string get;
			if (tempData.size() != 0) {
				getline(q, get, ',');
				
				temp_Track.id = stoi(get);
				tempData.erase(0, get.size() + 13);

				int pos = tempData.find(')');
				if (pos != string::npos) {
					temp_Track.geometry = tempData.substr(0, pos);
					tempData.erase(0, pos + 3);
				}
				pos = tempData.find_last_of(',');
				temp_Track.city_id = stoi(tempData.substr(pos + 1, tempData.size() - pos - 1));
				//temp_Track.geometry = tempData;

				obj->insertHead(temp_Track);
			}
			else isok = true;
		}
		i++;
	}
	//if(isok==0)
	obj->reverse();
	return obj;
	

	

}

bool track_id(Track &t1, int &t2) {
	return t1.id == t2;
}


bool track_cityid(Track &t1, int &t2) {
	return t1.city_id == t2;
}

void LoadData(void * & p) {
	Dataset * res = new Dataset;
	res->city = readCity();
	res->line = readLine();
	res->station = readStation();
	res->stationLine = readStation_line();
	res->track = readTrack();
	p = res;
//	for (int i = 0; i < res->city->getSize(); i++) cout << res->city->at(i).name<<"\n";
}

void ReleaseData(void* &p){
	
}



