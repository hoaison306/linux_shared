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

/* TODO: You can implement methods, functions that support your data structures here.
 * */
#include "dbLib.h"
using namespace std;

void Initialization() {
    // If you use global variables, please initialize them explicitly in this function.
}

void Finalization() {
    // Release your data before exiting
}

void ProcessRequest(const char* pRequest, void* pData, void*& pOutput, int& N) {
	// TODO: Implement this function for processing a request
	// NOTE: You can add other functions to support this main process.
	//       pData is a pointer to a data structure that manages the dataset
	//       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
	//       N is the size of output, must be a non-negative number
	TDataset* data = static_cast<TDataset*>(pData);
	string pR = static_cast<string>(pRequest);
	TStation max = data->dataStation.findMax(compareStation_id);
	int id_max = max.id;
	if (pR == "CL") {
		int size = data->dataLine.getSize();
		int* p = new int(size);
		pOutput = p;
		N = 1;
	}
	if (pR.substr(0, 2) == "CL" && pR.size() > 2) {
		string city_name = pR.substr(3, pR.size() - 3);
		TCity temp, p;
		temp.name = city_name;
		int resultfind = data->dataCity.findFirst(isEqualTCity_name, temp, p);
		if (resultfind == -1) {
			int* a = new int(-1);
			pOutput = a;
		}
		else {
			int size = 0;
			TLine tempLine;
			tempLine.city_id = p.id;
			int resultsize = data->dataLine.findSize(isEqualTLine_cityid, tempLine, size);
			if (resultsize == 0) {
				int* a = new int(size);
				pOutput = a;
			}
			else {
				int* a = new int(0);
				pOutput = a;
			}
		}
		N = 1;
	}
	if (pR.substr(0, 3) == "LSC" && pR.size() > 3) {//1.4s
		string city_name = pR.substr(4, pR.size() - 4);
		TCity temp, p;
		temp.name = city_name;
		int resultfind = data->dataCity.findFirst(isEqualTCity_name, temp, p);
		if (resultfind == -1) {
			int* a = new int(0);
			pOutput = a;
			N = 0;
		}
		else {
			int size = 0;
			TStation tempStation;
			tempStation.city_id = p.id;
			int resultsize = data->dataStation.findSize(isEqualTStation_cityid, tempStation, size);
			if (resultsize == 0) {
				TStation* a;
				a = data->dataStation.findArr(isEqualTStation_cityid, tempStation, size);
				int* st_id = new int[size];
				for (int i = 0; i < size; i++) st_id[i] = a[i].id;
				pOutput = st_id;
				N = size;
			}
			else {
				int* a = new int(0);
				pOutput = a;
				N = 0;
			}
		}
	}
	if (pR.substr(0, 3) == "LLC" && pR.size() > 3) {//0.059s
		string city_name = pR.substr(4, pR.size() - 4);
		TCity temp, p;
		temp.name = city_name;
		int resultfind = data->dataCity.findFirst(isEqualTCity_name, temp, p);
		if (resultfind == -1) {
			int* a = new int(0);
			pOutput = a;
			N = 0;
		}
		else {
			int size = 0;
			TLine tempLine;
			tempLine.city_id = p.id;
			int resultsize = data->dataLine.findSize(isEqualTLine_cityid, tempLine, size);
			if (resultsize == 0) {
				TLine* a;
				a = data->dataLine.findArr(isEqualTLine_cityid, tempLine, size);
				int* line_id = new int[size];
				for (int i = 0; i < size; i++) line_id[i] = a[i].id;
				pOutput = line_id;
				N = size;
			}
			else {
				int* a = new int(-1);
				pOutput = a;
				N = 0;
			}
		}
	}
	if (pR.substr(0, 3) == "LSL" && pR.size() > 3) {//thieu truong hop line_id khong co trong lines.csv
		int line_id = stoi(pR.substr(4, pR.size() - 4));
		TLine tempLine, p;
		tempLine.id = line_id;
		int resultfind = data->dataLine.findFirst(isEqualTLine_id, tempLine, p);
		if (resultfind == -1) {
			int* a = new int(0);
			pOutput = a;
			N = 0;
		}
		else {
			TStation_Line tempStationLine;
			tempStationLine.line_id = line_id;
			int size = 0;
			int resultsize = data->dataStation_Line.findSize(isEqualTStationLine_lineid, tempStationLine, size);
			if (resultsize == 0) {
				TStation_Line* a;
				a = data->dataStation_Line.findArr(isEqualTStationLine_lineid, tempStationLine, size);
				int* st_id = new int[size];
				for (int i = 0; i < size; i++) st_id[i] = a[i].station_id;
				pOutput = st_id;
				N = size;
			}
			else {
				int* a = new int(-1);
				pOutput = a;
				N = 0;
			}
		}
	}
	if (pR.substr(0, 2) == "FC" && pR.size() > 2) {
		string city_name = pR.substr(3, pR.size() - 3);
		TCity temp, p;
		temp.name = city_name;
		int resultfind = data->dataCity.findFirst(isEqualTCity_name, temp, p);
		if (resultfind == 0) {
			int* a = new int(p.id);
			pOutput = a;
		}
		else {
			int* a = new int(-1);
			pOutput = a;
		}
		N = 1;
	}
	if (pR.substr(0, 2) == "FS" && pR.size()>2) {
		string station_name = pR.substr(3, pR.size() - 3);
		TStation temp, p;
		temp.name = station_name;
		int resultfind = data->dataStation.findFirst(isEqualTStation_name, temp, p);
		if (resultfind == 0) {
			int* a = new int(p.id);
			pOutput = a;
		}
		else {
			int* a = new int(-1);
			pOutput = a;
		}
		N = 1;
	}
	if (pR.substr(0, 3) == "SLP" && pR.size() > 3) {
		stringstream s;
		s << pR;
		string temp;
		getline(s, temp, ' ');
		getline(s, temp, ' ');
		int station_id = stoi(temp);
		getline(s, temp);
		int track_id = stoi(temp);
		TStation tempStation, pS;
		tempStation.id = station_id;
		int resultfind1 = data->dataStation.findFirst(isEqualTStation_id, tempStation, pS);
		if (resultfind1 == 0) {
			TTrack tempTrack, pT;
			tempTrack.id = track_id;
			int resultfind2 = data->dataTrack.findFirst(isEqualTTrack_id, tempTrack, pT);
			if (resultfind2 == 0) {
				if (pT.geometry.find(pS.geometry) != string::npos) {
					stringstream ss;
					ss << pT.geometry;
					string word;
					int index = 0;
					while (getline(ss, word, ',')) {
						if (word != pS.geometry) index++;
						else break;
					}
					if (word == "") {
						int* a = new int(-1);
						pOutput = a;
					}
					else {
						int* a = new int(index);
						pOutput = a;
					}
				}
				else {
					int* a = new int(-1);
					pOutput = a;
				}
			}
			else {
				int* a = new int(-1);
				pOutput = a;
			}
		}
		else {
			int* a = new int(-1);
			pOutput = a;
		}
		N = 1;
	}
	if (pR.substr(0, 3) == "IS " && pR.size() > 3) {
		string data_csv = pR.substr(3, pR.size() - 3);
		TStation temp;
		size_t first = data_csv.find("POINT");
		size_t second = data_csv.find('(', first + 1);
		size_t third = data_csv.find(')', first + 1);
		string secondhalf = data_csv.substr(third + 2, data_csv.size() - third - 2);
		temp.name = data_csv.substr(0, first - 1);
		temp.geometry = data_csv.substr(second + 1, third - second - 1);
		stringstream ss;
		ss << secondhalf;
		string word;
		temp.id = ++id_max;
		temp.city_id = 0;
		data->dataStation.push_back(temp);
		int* p = new int(id_max);
		pOutput = p;
		N = 1;
	}
	if (pR.substr(0, 3) == "RS " && pR.size() > 3) {
		bool isFound = false;
		int station_id = stoi(pR.substr(3, pR.size() - 3));
		int iStation = 0;
		TStation temp, save;
		TStation_Line temp1, save1;
		temp.id = station_id;
		temp1.station_id = station_id;
		int resultremove = data->dataStation.remove(isEqualTStation_id, temp, save);
		if (resultremove == 0) {
			if (id_max == station_id) id_max--;
			int resultremove1 = data->dataStation_Line.remove(isEqualTStationLine_stationid, temp1, save1);
			L1Item<TTrack>* head = data->dataTrack.getHead();
			while (head != nullptr) {
				string word;
				stringstream s;
				s << head->data.geometry;
				if (head->data.geometry.size() > 0) {
					while (getline(s, word, ',')) {
						if (word == save.geometry) {
							size_t first = head->data.geometry.find(word);
							if (first == 0)	head->data.geometry.erase(first, word.size() + 1);
							else head->data.geometry.erase(first - 1, word.size() + 1);
							break;
						}
					}
				}
				head = head->pNext;
			}
			int* p = new int(0);
			pOutput = p;
		}
		else {
			int* p = new int(-1);
			pOutput = p;
		}
		N = 1;
	}
	if (pR.substr(0, 2) == "US" && pR.size() > 2) {
		stringstream s;
		string buf;
		s << pR;
		getline(s, buf, ' ');
		getline(s, buf, ' ');
		int station_id = stoi(buf);
		getline(s, buf);
		string data_csv = buf;
		TStation temp, p, save;
		temp.id = station_id;

		size_t first = data_csv.find("POINT");
		p.name = data_csv.substr(0, first);
		p.geometry = data_csv.substr(first + 6, data_csv.find(")") - first - 6);
		int resultupdate = data->dataStation.findUpdate(isEqualTStation_id, temp, p, save);
		L1Item<TTrack>* head = data->dataTrack.getHead();
		while (head != nullptr) {
			string word;
			stringstream s;
			s << head->data.geometry;
			if (head->data.geometry.size() > 0) {
				while (getline(s, word, ',')) {
					if (word == save.geometry) {
						size_t first = head->data.geometry.find(word);
						head->data.geometry.replace(first, word.size(), p.geometry);
						break;
					}
				}
			}
			head = head->pNext;
		}
		int* a = new int(resultupdate);
		pOutput = a;
		
		N = 1;
	}
	if (pR.substr(0, 3) == "ISL" && pR.size() > 3){
		stringstream s;
		string temp;
		s << pR;
		getline(s, temp, ' ');
		getline(s, temp, ' ');
		int station_id = stoi(temp);
		getline(s, temp, ' ');
		int line_id = stoi(temp);
		getline(s, temp);
		int p_i = stoi(temp);
		TStation tempSt, pSt;
		tempSt.id = station_id;
		TLine tempLine, pL;
		tempLine.id = line_id;
		//int check_stid = data->dataStation.findFirst(isEqualTStation_id, tempSt, pSt);
		//if (check_stid == 0) {
			int check_lid = data->dataLine.findFirst(isEqualTLine_id, tempLine, pL);
			if (check_lid == 0) {
				TStation_Line tempStL, pStL;
				tempStL.line_id = line_id;
				tempStL.station_id = station_id;
				int check_stid_lid = data->dataStation_Line.findFirst(compareStID_LineID, tempStL, pStL);
				if (check_stid_lid == -1) {
					int size = 0;
					data->dataStation_Line.findSize(isEqualTStationLine_lineid, tempStL, size);
					if (p_i < size) {
						int resultupdate = data->dataStation_Line.insertAtIdx(isEqualTStationLine_lineid, tempStL, tempStL, p_i, false);
						int* a = new int(0);
						pOutput = a;
					}
					else if (p_i == size) {
						int resultupdate = data->dataStation_Line.insertAtIdx(isEqualTStationLine_lineid, tempStL, tempStL, p_i, true);
						int* a = new int(0);
						pOutput = a;
					}
					else {
						int* a = new int(-1);
						pOutput = a;
					}
				}
				else {
					int* a = new int(-1);
					pOutput = a;
				}
			}
			else {
				int* a = new int(-1);
				pOutput = a;
			}
		/*}
		else {
			int* a = new int(-1);
			pOutput = a;
		}*/
		N = 1;
	}//chua xong
	if (pR.substr(0, 3) == "RSL" && pR.size() > 3) {
		stringstream s;
		string temp;
		s << pR;
		getline(s, temp, ' ');
		getline(s, temp, ' ');
		int station_id = stoi(temp);
		getline(s, temp);
		int line_id = stoi(temp);
		TStation_Line tempStL;
		tempStL.station_id = station_id;
		tempStL.line_id = line_id;
		int resultfind = data->dataStation_Line.removeWithData(compareStID_LineID, tempStL);
		int* a = new int(resultfind);
		pOutput = a;
		N = 1;
	}


}

