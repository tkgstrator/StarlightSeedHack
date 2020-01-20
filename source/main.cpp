#include "main.hpp"
#include "coop.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <omp.h>
#define Q "1111111"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    string wave = argv[1]; 
    u32 range = atof(argv[2]); 
    // if (argc == 3)
    //     std::string geyser = argv[3];

    cout << "Hello Starlight!" << endl;
    ofstream ofs("seeds.txt");
    clock_t start = clock();

#ifdef _OPENMP
    u16 threads = omp_get_max_threads();
    cout << "Threads:" << omp_get_max_threads() << ", Num:" << range << endl;
#else
    u16 threads = 1;
#endif
#pragma omp parallel for
    for (u32 seed = 0x0; seed < range; ++seed)
    {
        coop::Seedhack tkg;
        tkg.init(seed);
        string info = tkg.getWaveInfo();

        // std::vector<std::string> gpos = tkg.getGeyser(4);
    }
    clock_t end = clock();
    const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0 / threads;
    cout << time << "ms" << endl;
    return 0;
}