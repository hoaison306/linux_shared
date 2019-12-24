#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>
#include <time.h>
#include "dsaLib.h"
#include "dbLib.h"
#include "processData.h"

using namespace std;

int main() {
	

    Initialization();

    void*   pData = nullptr;
    void*   pOutput = nullptr;
    int     N;
	clock_t start = clock();
	double duration1;
	start = std::clock();
   LoadData(pData);
  // duration1 = (std::clock() - start) / (double)CLOCKS_PER_SEC;
  // std::cout << "printf: " << duration1 << '\n';
   assert(pData != nullptr);
    cout << fixed << setprecision(8);
    string req;
	ifstream ff;
	ff.open("Text1.txt");
    while (true) {
        req = "";
        getline(ff, req);
        if (ff.bad()) {
            ff.clear();
            ff.ignore(1024, '\n');
            continue;
        }
        if (req == "Exit") {
            break;
        }
		clock_t qq = clock();

        ProcessRequest(req.data(), pData, pOutput, N);
		//cout << "\n" << N;
        PrintReqOutput<int>(req.data(), (int*)pOutput, N);
		//clock_t end = clock();
		//cout << double(end - qq) / CLOCKS_PER_SEC << '\n';
		

        delete [] (int*)pOutput;
        pOutput = nullptr;
    }
	//ProcessRequest("LSC Santiago", pData, pOutput, N);

   ReleaseData(pData);
    Finalization();
	
	/*duration1 = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	std::cout << "printf: " << duration << '\n';*/
	
	system("pause");
    return 0;
}