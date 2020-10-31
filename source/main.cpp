#include "main.hpp"
#include "coop.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <omp.h>
#include <cmath>
#include <math.h>
#include <unistd.h>
#include <algorithm>
#ifdef _OPENMP
u16 threads = omp_get_max_threads();
#else
u16 threads = 1;
#endif

using namespace std;
#define N 0x100000

int main(int argc, char **argv)
{
    std::ofstream ofs;
    std::vector<string> mBuffer;
    ofs.open("EasyWave3[3].txt");
    std::ifstream ifs; // Input File

    // #pragma omp parallel for
    for (u8 omp = 0x0; omp < 0x10; ++omp)
    {
        std::ifstream ifs; // Input File
        ifs.open("202020[" + std::to_string(omp) + "].txt");

        std::string line;
        for (; getline(ifs, line);)
        {
            ostringstream sout;
            u32 mSeed = static_cast<unsigned int>(std::stol(line.substr(0, 10), NULL, 0));
            Coop::Ocean mOcean = Coop::Ocean(mSeed);
            if (mOcean.mWaveMgr[2].isEasyWave(3))
            {
                sout << std::setw(8) << std::uppercase << std::setfill('0') << hex << mSeed << ","
                     << "202020,"
                     << "EnemyAppearId = 3";
                mBuffer.push_back(sout.str());
            }
        }
        for (auto line : mBuffer) // Output
            ofs << line << endl;
        // for (u32 seed = 0x0; seed < N; ++seed)
        // {
        //     const u32 mInitialSeed = seed + N * omp;
        //     Coop::Ocean mOcean = Coop::Ocean(mInitialSeed);
        //     if (mOcean.mWaveMgr[2].isEasyWave())
        //         printf("Seed:->%08X\n", mInitialSeed);
        // }
    }
}
