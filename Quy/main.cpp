#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>
#include <fstream>
#include "dsaLib.h"
#include "dbLib.h"
#include "processData.h"

using namespace std;

int main() {
    Initialization();

    void*   pData = nullptr;
    void*   pOutput = nullptr;
    int     N;
	ifstream inFile;
	inFile.open("input.txt");
    LoadData(pData);
    assert(pData != nullptr);
    cout << fixed << setprecision(8);
    string req;
  //  while (getline(inFile, req)) {
  //      //req = "";
  //     /* getline(cin, req);
  //      if (cin.bad()) {
  //          cin.clear();
  //          cin.ignore(1024, '\n');
  //          continue;
  //      }*/
  //      if (req == "Exit") {
  //          break;
  //      }
  //      ProcessRequest(req.data(), pData, pOutput, N);
		//std::cout << "N = " << N << '\n';
  //      PrintReqOutput<int>(req.data(), (int*)pOutput, N);
  //      delete [] (int*)pOutput;
  //      pOutput = nullptr;
  //  }
	while (true) {
		req = "";
		getline(cin, req);
		if (cin.bad()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (req == "Exit") {
			break;
		}
		ProcessRequest(req.data(), pData, pOutput, N);
		PrintReqOutput<int>(req.data(), (int*)pOutput, N);
		delete[](int*)pOutput;
		pOutput = nullptr;
	}
    ReleaseData(pData);
    Finalization();
	system("pause");
    return 0;
}