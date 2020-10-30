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
#define N 0x1

int main(int argc, char **argv)
{
    // #pragma omp parallel for
    for (u8 omp = 0x0; omp < 0x1; ++omp)
    {
        for (u32 seed = 0x0; seed < N; ++seed)
        {
            const u32 mInitialSeed = seed + N * omp;
            Coop::Ocean mOcean = Coop::Ocean(mInitialSeed);
            printf("\rSeed:->%X %X", mInitialSeed, mOcean.mWaveMgr[2].mWaveSeed);
            break;
        }
    }
    printf("\n");
}
