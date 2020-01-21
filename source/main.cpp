#include "main.hpp"
#include "coop.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <omp.h>
#include <algorithm>
#ifdef _OPENMP
u16 threads = omp_get_max_threads();
#else
u16 threads = 1;
#endif

using namespace std;

int main(int argc, char **argv)
{
    // Initial
    bool sflag = false;
    bool gflag = false;
    u16 stage_id;
    u32 range;
    string wave, seq;
    vector<string> seeds;
    ofstream ofs("seeds.txt");
    clock_t start = clock();
    for (u16 i = 1; i < argc; ++i)
    {
        cout << i << " : " << argv[i] << endl;
        if (argc < 2)
            return -1;
        if (i == 1)
            wave = argv[1];
        if (i == 2)
            range = atof(argv[2]);
        if (!strcmp(argv[i], "-S"))
        {
            sflag = true;
            stage_id = atoi(argv[i + 1]);
        }
        if (!strcmp(argv[i], "-G"))
        {
            gflag = true;
            seq = argv[i + 1];
        }
    }

    cout << "Hello Starlight!" << endl;
    cout << "Settings: Threads(" << threads << ") Wave(" << wave << ") Range:(" << range << ")" << endl;

#pragma omp parallel for
    for (u32 seed = 0x0; seed <= range; ++seed)
    {
        coop::Seedhack tkg;
        tkg.init(seed);
        string waveinfo = tkg.getWaveInfo();
        if (regex_search(waveinfo, regex(wave)))
        {
            ostringstream sout;
            // sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;

            if (sflag) // Setting Stage ID
            {
                tkg.set(stage_id);
                // Geyser Matching
                if (regex_search(waveinfo, regex("22..22")))
                {
                    std::vector<std::string> gpos = tkg.getGeyser();
                    if (gflag)
                    {
                        if (regex_search(gpos[0], regex(seq)) || regex_search(gpos[2], regex(seq)))
                        {
                            sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                            sout << "," << gpos[0] << "," << gpos[2];
                            seeds.push_back(sout.str());
                        }
                    }
                    else
                    {
                        sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                        sout << "," << gpos[0] << "," << gpos[2];
                        seeds.push_back(sout.str());
                    }
                }
                else
                {
                    std::vector<std::string> gpos = tkg.getGeyser();
                    if (regex_search(waveinfo, regex("22....")))
                    {
                        sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                        sout << "," << gpos[0];
                        seeds.push_back(sout.str());
                    }
                    if (regex_search(waveinfo, regex("..22..")))
                    {
                        sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                        sout << "," << gpos[1];
                        seeds.push_back(sout.str());
                    }
                    if (regex_search(waveinfo, regex("....22")))
                    {
                        sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                        sout << "," << gpos[2];
                        seeds.push_back(sout.str());
                    }
                }
            }
            else
            {
                sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                seeds.push_back(sout.str());
            }
        }
    }
    sort(seeds.begin(), seeds.end()); // Sorting
    for (auto val : seeds)            // Output
    {
        ofs << val << endl;
    }
    clock_t end = clock();
    const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0 / threads;
    cout << time << "ms" << endl;
    return 0;
}