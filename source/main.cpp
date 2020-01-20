#include "main.hpp"
#include "coop.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <omp.h>
#define N 0xFFFFFF
#define Q "11111111"

using namespace std;

int main(int argc, char **argv)
{
    ostringstream sout;
    coop::Seedhack tkg;
    ofstream ofs("seeds.txt");
    clock_t start = clock();

    cout << "Hello Starlight!" << endl;
#ifdef _OPENMP
    cout << "Threads:" << omp_get_max_threads() << ", Num:" << N << endl;
#endif
#pragma omp parallel for num_threads(1)
    for (u32 seed = 0x0; seed < N; seed++)
    {
        tkg.init(seed);
        sout.str("");
#pragma omp critical
        sout << setfill('0') << right << setw(6) << dec << tkg.getWaveInfo();
        string info = sout.str();

        string::size_type index[2] = {info.find("22"), info.rfind("22")};
        if ((index[0] != string::npos) && (index[0] % 2 == 0))
        {
            tkg.getGeyser(4);                                  // Calculate
            if ((index[0] != index[1]) && (index[1] % 2 == 0)) // W1 and W3
            {
                if (tkg.gpos[0].find(Q) != string::npos || tkg.gpos[2].find(Q) != string::npos)
                {
                    ofs << "0x" << setw(8) << uppercase << setfill('0') << hex << seed;
                    ofs << "," << info << "," << tkg.gpos[0] << "," << tkg.gpos[2] << endl;
                }
            }
            else
            {
                if (tkg.gpos[info.find("22") / 2].find(Q) != string::npos)
                {
                    ofs << "0x" << setw(8) << uppercase << setfill('0') << hex << seed;
                    ofs << "," << info << "," << tkg.gpos[info.find("22") / 2] << endl;
                }
            }
        }
    }
    clock_t end = clock();
    const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    cout << time << "s" << endl;
}