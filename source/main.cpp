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
static const regex w13 = regex("22..22");
static const regex w01 = regex("^(?!.*.{4}22).*(?=22.{4}).*$");
static const regex w02 = regex("..22..");
static const regex w03 = regex("^(?!.*22.{4}).*(?=.{4}22).*$");

int main(int argc, char **argv)
{
    // Initial
    bool sflag = false; // Stage ID Flag.
    bool rflag = false; // Regex for WAVE Information Flag.
    bool gflag = false; // Regex for Geyser Sequence Flag.
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
        if (!strcmp(argv[i], "-R"))
        {
            rflag = true;
        }
    }

    cout << "Welcome Starlight SeedHack!" << endl;
    cout << "Settings: Threads(" << threads << ") Wave(" << wave << ") Range:(" << range << ")" << endl;

#pragma omp parallel for
    for (u32 seed = 0x0; seed < range; ++seed)
    {
        coop::Seedhack tkg;
        tkg.init(seed);
        string waveinfo = tkg.getWaveInfo();
        // if (regex_match(waveinfo, regex(wave)))
        if (!rflag ? waveinfo == wave : regex_match(waveinfo, regex(wave)))
        {
            ostringstream sout;
            tkg.set(stage_id);
            if (!sflag) // Checking Stage ID
            {
                sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
            }
            if (regex_match(waveinfo, w13) && sflag)
            {
                std::vector<std::string> gpos = tkg.getGeyser();
                if ((regex_search(gpos[0], regex(seq)) || regex_search(gpos[2], regex(seq))) || !gflag)
                {
                    sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                    sout << "," << gpos[0] << "," << gpos[2];
                }
            }
            if (regex_match(waveinfo, w01) & sflag)
            {
                std::vector<std::string> gpos = tkg.getGeyser();
                if ((regex_search(gpos[0], regex(seq)) && gflag) || !gflag)
                {
                    sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                    sout << "," << gpos[0];
                }
            }
            if (regex_match(waveinfo, w02) & sflag)
            {
                std::vector<std::string> gpos = tkg.getGeyser();
                if ((regex_search(gpos[1], regex(seq)) && gflag) || !gflag)
                {
                    sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                    sout << "," << gpos[1];
                }
            }
            if (regex_match(waveinfo, w03) & sflag)
            {
                std::vector<std::string> gpos = tkg.getGeyser();
                if ((regex_search(gpos[2], regex(seq)) && gflag) || !gflag)
                {
                    sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                    sout << "," << gpos[2];
                }
            }
            if (sout.str() != "")
                seeds.push_back(sout.str());
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