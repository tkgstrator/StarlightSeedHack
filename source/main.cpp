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
    u16 stage_id = 4;
    u32 range = 0xFFFF;
    string wave, seq;
    vector<string> seeds;
    ofstream ofs("seeds.txt");
    clock_t start = clock();
    wave = "22..22";

    cout << "Welcome Starlight SeedHack!" << endl;
    cout << "Made by : tkgstrator" << endl;
    cout << "Thanks  : shadowninja108" << endl;
    cout << "        : container12345" << endl;
    cout << "Threads : " << threads << endl;
    cout << "Wave    : " << wave << endl;
    cout << "Range   : " << range << endl;
    cout << "Stage   : " << stage_id << endl;
    // cout << "Regex   : " << (rflag ? "Enable" : "Disable")<< endl;
    // cout << "Geyser  : " << (sflag ? "Enable" : "Disable") << endl;
    // cout << "Sequence: " << (gflag ? "Enable" : "Disable") << endl;

    // Checking Arguments.
    for (u16 i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-r"))
        { // Load Seeds from text file.
            std::ifstream ifs(argv[i + 1]);
            if (ifs.fail())
            {
                std::cout << "No such file on directory." << std::endl;
                return -1;
            }

        }
    }

    rflag = true;
#pragma omp parallel for
    for (u32 seed = 0x0; seed < range; ++seed)
    {
        if (seed % (range / 1000) == 0)
        {
            std::cout << (double(seed) / double(range)) * 100 << "%" << std::endl;
        }
        Coop::Seedhack tkg;
        tkg.init(seed); // Set First seed.
        string waveinfo = tkg.getWaveInfo();
        if (!rflag ? waveinfo == wave : regex_match(waveinfo, regex(wave)))
        {
            ostringstream sout;
            std::vector<std::string> gpos = tkg.getGeyser(stage_id);
            if (regex_match(waveinfo, w13)) // Wave1 and Wave3
            {
                if ((regex_search(gpos[0], regex(seq)) || regex_search(gpos[2], regex(seq))))
                {
                    sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                    sout << "," << gpos[0] << "," << gpos[2];
                }
            }
            if (regex_match(waveinfo, w01)) // Wave1
            {
                if ((regex_search(gpos[0], regex(seq))))
                {
                    sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                    sout << "," << gpos[0];
                }
            }
            if (regex_match(waveinfo, w02)) // Wave2
            {
                if ((regex_search(gpos[1], regex(seq))))
                {
                    sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
                    sout << "," << gpos[1];
                }
            }
            if (regex_match(waveinfo, w03)) // Wave3
            {
                if ((regex_search(gpos[2], regex(seq))))
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
    const double time = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000.0 / threads;
    cout << "Time    : " << time << "ms" << endl;
    return 0;
}