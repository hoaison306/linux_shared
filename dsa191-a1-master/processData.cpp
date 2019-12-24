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


void ProcessRequest(const char* pRequest, void* pData, void* &pOutput, int &N) {
	// TODO: Implement this function for processing a request
	// NOTE: You can add other functions to support this main process.
	//       pData is a pointer to a data structure that manages the dataset
	//       pOutput is a pointer reference. It is set to nullptr and student must allocate data for it in order to save the required output
	//       N is the size of output, must be a non-negative number 
	Dataset* p = static_cast<Dataset*>(pData);

	
	string q(pRequest);

	//CL
	if (q == "CL") {
		int count = p->line->getSize();
		int * res = new int(count);
		pOutput = res;
		N = 1;
		//cout << count;
	}

	//CL <city_name>
	else if (q.size() > 2 && q.substr(0, 2) == "CL") {
		int count = 0;
		string city_name(pRequest);
		int begin = city_name.find_first_of(' ');
		int end = city_name.find('\0');
		city_name = city_name.substr(begin + 1, end - begin - 1);
		string temp;
		int i = 0;
		int size = p->city->getSize();
		temp = p->city->at(0).name;
		bool isExist = 0;
		i = p->city->idx_cityName(p_idx_name, city_name);
		if (i != -1) isExist = 1;

		if (isExist == 1) {
			int city_id = p->city->at(i).id;
			/*for (int i = 0; i < p->line->getSize(); i++) {
				if (p->line->at(i).city_id == city_id) count++;
			}*/
			count = p->line->count_cityID(p_idx_id, city_id);
			int *res = new int(count);
			pOutput = res;
			N = 1;
		}
		else {
			count = -1;
			int *res = new int(count);
			pOutput = res;
			N = 1;
		}


		//N = count;

	}

	//LSC <city_name>
	else if (q.substr(0, 3) == "LSC") {

		int* station;
		string city_name(pRequest);
		int begin = city_name.find_first_of(' ');
		int end = city_name.find('\0');
		city_name = city_name.substr(begin + 1, end - begin - 1);
		int size = p->city->getSize();
		int i;
		i = p->city->idx_cityName(p_idx_name, city_name);
		if (i < 0) {
			N = 1;
			pOutput = new int(-1);
		}
		else {
			int id_city = p->city->at(i).id;
			int size_station = p->station->getSize();
			int count = 0;
			bool isTrue = 0;
			count = p->station->count_station_cityID(station_cityID, id_city);
			//	if (count != 0) {
			int* temp = new int[count];
			int order = 0;
			int* q;
			q = p->station->get_idxStation_cityID_equal(station_cityID, id_city);
			while (order < count) {
				temp[order] = p->station->at(q[order]).id;
				order++;
			}
			pOutput = temp;
			N = count;
			//}
		/*	else {
				pOutput = new int(-1);
				N = 1;
			}*/
		}
	}

	//LLC <city_name>
	else if (pRequest[0] == 'L'&& pRequest[1] == 'L'&& pRequest[2] == 'C') {
		int* line;
		string city_name(pRequest);
		int begin = city_name.find_first_of(' ');
		int end = city_name.size();
		city_name = city_name.substr(begin + 1, end - begin - 1);
		int size = p->city->getSize();
		int i;
		i = p->city->idx_cityName(p_idx_name, city_name);
		if (i < 0) {
			int* qq = new int(-1);
			pOutput = qq;
			N = 1;
		}
		else {
			int id_city = p->city->at(i).id;
			int count = 0;
			count = p->line->count_line_cityID(line_city_id, id_city);
			int*temp = new int[count];
			int order = 0;
			int*q;
			q = p->line->get_idxLine_cityID_equal(line_city_id, id_city);
			while (order < count) {
				temp[order] = p->line->at(q[order]).id;
				order++;
			}
			pOutput = temp;
			N = count;

		}
	}
	
	//LSL <line_id>
	else if (pRequest[0] == 'L' && pRequest[1] == 'S' && pRequest[2] == 'L') {
		int* res;
		int line_id;
		string data(pRequest);
		int begin = data.find(' ');
		int end = data.find('\0');
		data = data.substr(begin + 1, end - begin - 1);
		line_id = stoi(data);
		int count = 0;
		count = p->stationLine->count_stationLine_line_id(stationLine_line_id, line_id);
		int* temp = new int[count];
		int index = 0;
		int* q;
		q = p->stationLine->get_idxStationLine_lineID_equal(stationLine_line_id, line_id);
		if (count <= 0) {
			N = 1;
			pOutput = new int(-1);
		}
		else {
			while (index < count) {
				temp[index] = p->stationLine->at(q[index]).station_id;
				index++;
			}
			pOutput = temp;
			N = count;
			
		}
	}

	//FC <city_name>
	else if (pRequest[0] == 'F' && pRequest[1] == 'C') {
		string name(pRequest);
		int begin = name.find(' ');
		int end = name.find('\0');
		name = name.substr(begin + 1, end - begin - 1);
		int res;	
		bool check = p->city->isFound_city_cityName(p_idx_name, name);		
		if (check==1) {
			int i = p->city->idx_cityName(p_idx_name, name);
			res = p->city->at(i).id;
			int* QQ = new int(res);
			pOutput = QQ;
			N = 1;
		}
		else {
			int* QQ = new int(-1);
			pOutput = QQ;
			N = 1;
		}
	}

	//FS <station_name>
	else if (pRequest[0] == 'F' && pRequest[1] == 'S' && q.size()>2) {
		string name(pRequest);
		int begin = name.find(' ');
		int end = name.find('\0');
		name = name.substr(begin + 1, end - begin - 1);
		bool isFound = 0;
		int res;	
		isFound = p->station->isFound_station_name(station_name, name);
		int i = p->station->getIndex_station_name(station_name, name);
		if (isFound) {
			res = p->station->at(i).id;
			int* QQ = new int(res);
			pOutput = QQ;
			N = 1;
		}
		else {
			int* QQ = new int(-1);
			pOutput = QQ;
			N = 1;
		}
	}

	//SLP <station id> <track_id>
	else if (pRequest[0] == 'S' && pRequest[1] == 'L' && pRequest[2] == 'P') {
		int res = -1;
		string data(pRequest);
		int s_id;
		int t_id;
		int begin = data.find_first_of(' ');
		int end = data.find_last_of(' ');
		s_id = stoi(data.substr(begin + 1, end - begin - 1));
		begin = end;
		end = data.find('\0');
		t_id = stoi(data.substr(begin + 1, end - begin - 1));			
		int i = p->station->getIndex_station_id_equal(station_id, s_id);
		int j;	
		j = p->track->getIndex_track_id_equal(track_id, t_id);
		
		string track = p->track->at(j).geometry;
		string station = p->station->at(i).geometry;
		if (track.find(station) != string::npos) {
			int count = 0;
			int countComma = 0;
			stringstream s(track);
			string get;
			int i = 0;
			while (track[i] != '\0') {
				if (track[i] == ',') countComma++;
				i++;
			}
			while (getline(s, get, ',')) {
				if (get != station) count++;
				else break;
			}
			if (count <= countComma  ) {
				int *qq = new int(count);
				pOutput = qq;
				N = 1;
			}
			else {
				int *qq = new int(-1);
				pOutput = qq;
				N = 1;
			}
		}
		else {
			int *qq = new int(-1);
			pOutput = qq;
			N = 1;
		}

	}

	//IS <csv Des>
	else if (q.substr(0,3)=="IS " && q.size()>2) {
	string name;
	string geometry;
	int buildStart;
	int opening;
	int closure;
	Station temp;
	int id, city_id;
	int pos;
	pos = q.find("POINT");
	name = q.substr(3, pos - 4);
	temp.name = name;
	q.erase(0, pos + 6);
	pos = q.find(')');
	geometry = q.substr(0, pos);
	temp.geometry = geometry;
	q.erase(0, pos + 2);
	pos=q.find_first_of(',');
	buildStart = stoi(q.substr(0, pos));
	temp.buildStart = buildStart;
	q.erase(0, pos + 1);
	pos=q.find_first_of(',');
	opening = stoi(q.substr(0, pos));
	temp.opening = opening;
	q.erase(0, pos + 1);
	q.find(',');
	closure = stoi(q.substr(0, pos));
	temp.closure = closure;
	
	
	Station tempStation;
	tempStation = p->station->get_station_id_max(station_id_bt,tempStation);
	id = tempStation.id + 1;
	temp.id = id;
	p->station->push_back(temp);
	int*qq = new int(id);
	pOutput = qq;
	N = 1;
	}

	//RS <station_id>
	else if (q.substr(0, 3) == "RS " && q.size() > 2) {
		int pos = q.find(' ');
		int station_idX = stoi(q.substr(pos + 1, q.size() - pos - 1));
		
		bool isFound_Station = 0;
		int i = p->station->getIndex_station_id_equal(station_id, station_idX);
		string geo = p->station->at(i).geometry;
		if (i != -1) {
			p->station->remove(i);
			isFound_Station = 1;
			
		}
		bool isFound_SL = 0;
		int isDone;
		int j = p->stationLine->getIndex_stationLine_Stationid_equal(stationLine_station_id, station_idX);
		if (j != -1) {
			p->stationLine->remove(j);
			isFound_SL = 1;
		}
		for (int i = 0; i < p->track->getSize(); i++) {
			if (p->track->at(i).geometry.find(geo)!=-1) {
				int pos = p->track->at(i).geometry.find(geo);
				p->track->at(i).geometry.erase(pos, geo.size());
				if (p->track->at(i).geometry[0] == ',') p->track->at(i).geometry.erase(0, 1);
				else if (p->track->at(i).geometry[pos - 1] == ',') p->track->at(i).geometry.erase(pos - 1, 1);
			}
		}
		//cout << p->track->at(0).geometry;
		if (isFound_SL == 1 || isFound_Station == 1) {
			int* qq = new int(0);
			pOutput = qq;
			N = 1;
		}
		else {
			int* qq = new int(-1);
			pOutput = qq;
			N = 1;
		}
	}

	//US <station_id> <des>
	else if (q.substr(0, 2) == "US") {
		int station_idX;
		string new_station_name;
		string name;
		string geometry;
		int old_cityid;
		string old_geometry;
		int buildStart;
		int opening, closure, city_id;
		int pos = q.find_first_of(' ');
		q.erase(0, pos + 1);
		pos = q.find_first_of(' ');
		station_idX = stoi(q.substr(0, pos));
		int station_pos = p->station->getIndex_station_id_equal(station_id, station_idX);
		old_cityid = p->station->at(station_pos).city_id;
		old_geometry = p->station->at(station_pos).geometry;
		int i;
		bool isFound = 0;
		i = p->station->getIndex_station_id_equal(station_id, station_idX);
		if (i != -1) {
			isFound = 1;
		}
		if (isFound == 1) {
			q.erase(0, pos + 1);
			pos = q.find("POINT");
			name = q.substr(0, pos - 1);
			p->station->at(i).name = name;
			q.erase(0, pos + 6);
			pos = q.find(')');
			geometry = q.substr(0, pos);
			p->station->at(i).geometry = geometry;
			q.erase(0, pos + 2);
			pos = q.find_first_of(',');
			buildStart = stoi(q.substr(0, pos));
			p->station->at(i).buildStart = buildStart;
			q.erase(0, pos + 1);
			pos = q.find_first_of(',');
			opening = stoi(q.substr(0, pos));
			p->station->at(i).opening = opening;
			q.erase(0, pos + 1);
			pos = q.find(',');
			closure = stoi(q.substr(0, pos));
			p->station->at(i).closure = closure;
			q.erase(0, pos + 1);
			city_id = stoi(q);
			p->station->at(i).city_id = city_id;

			////Kiem tra trong Track
			//int i = p->track->getindex_track_cityid_equal(track_cityid, old_cityid);
			//if (i != -1) {
			//	int pos;
			//	string track = p->track->at(i).geometry;
			//	if (track.find(geometry) != string::npos) {
			//		int count = 0;
			//		stringstream s(track);
			//		string get;
			//		while (getline(s, get, ',')) {
			//			if (get != geometry) count++;
			//			else { 
			//				pos = track.find(geometry);
			//				break; 
			//			}
			//		}
			//		int countComma = 0;
			//		int i = 0;
			//		while (track[i] != '\0') {
			//			if (track[i] == ',') countComma++;
			//			i++;
			//		}
			//		if (count <= countComma) {
			//			if (count == 0) {
			//				int pos = track.find_first_of(',');
			//				track.erase(0, pos + 1);
			//				track = geometry + track;
			//			}
			//			else if (count == countComma) {
			//				int pos = track.find_last_of(',');
			//				track.erase(pos + 1, track.size() - pos - 1);
			//				track = track + geometry;
			//			}
			//			else {
			//				int pos = track.find(geometry);
			//				string ss = track.substr(pos, track.size() - pos);
			//				track.erase(pos, track.size() - pos);
			//				pos = ss.find_first_of(',');
			//				ss.erase(0, pos);
			//				ss = geometry + ss;
			//				track = track + ss;
			//			}
			//		}
			//	}
			//}
			int* qq = new int(0);
			pOutput = qq;
			N = 1;

		}
		else {
			int* qq = new int(-1);
			pOutput = qq;
			N = 1;
		}
	}

	//ISL <station_id> <line_id> <p_i>
	else if (q.substr(0, 3) == "ISL") {
		int station_idX, line_id, p_i;
		int pos = q.find_first_of(' ');
		q.erase(0, pos + 1);
		pos = q.find_first_of(' ');
		station_idX = stoi(q.substr(0, pos));
		q.erase(0, pos + 1);
		pos = q.find_first_of(' ');
		line_id = stoi(q.substr(0, pos));
		q.erase(0, pos + 1);
		p_i = stoi(q);
		bool isEqual = 0;
		bool isFound_station;
		isFound_station = p->station->isFound_station_station_id(station_id, station_idX);
		if (isFound_station == 1) {
			int size = p->stationLine->count_stationline_lineid_equal(stationLine_line_id, line_id);
			int* q = new int[size];
			q = p->stationLine->getindex_stationline_lineid_equal(stationLine_line_id, line_id);

			if (size != 0) {
				for (int i = 0; i < size; i++) {
					if (p->stationLine->at(q[i]).station_id == station_idX)
					{
						isEqual = 1; break;
					}
				}
			}
		}
		if (isEqual == 1) {
			int* qq = new int(-1);
			pOutput = qq;
			N = 1;
		}
		else {
			int k = p->stationLine->index_lineid_equal_pi_th(stationLine_line_id, line_id, p_i);
			if (k == -1) {
				int* qq = new int(-1);
				pOutput = qq;
				N = 1;
			}
			else {
				Station_line temp;
				temp.line_id = line_id;
				temp.station_id = station_idX;
				p->stationLine->insert(k, temp);
				int* qq = new int(0);
				pOutput = qq;
				N = 1;
			}
		}
	}
	

	//RSL <station_id> <line_id>
	else if (q.substr(0, 3) == "RSL") {
		int station_id, line_id;
		int pos = q.find_first_of(' ');
		q.erase(0, pos + 1);
		pos = q.find_first_of(' ');
		station_id = stoi(q.substr(0, pos));
		q.erase(0, pos + 1);
		line_id = stoi(q);
		bool isFound = 0;
		int i = 0;

		int size = p->stationLine->count_stationline_lineid_equal(stationLine_line_id, line_id);
		int* q = new int[size];
		q = p->stationLine->getindex_stationline_lineid_equal(stationLine_line_id, line_id);

		if (size != 0) {

			for (i = 0; i < size; i++) {
				if (p->stationLine->at(q[i]).station_id == station_id)
				{
					isFound = 1; break;
				}
			}
		}
		if (isFound == 1) {
			p->stationLine->remove(q[i]);
			int* qq = new int(0);
			pOutput = qq;
			N = 1;
		}
		else {
			int* qq = new int(-1);
			pOutput = qq;
			N = 1;
		}
	}

	else {
	pOutput = nullptr;
}
	
}
