#include "main.hpp"
#include "coop.h"
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
    std::string wave, seq;
    std::vector<bool> mMode = {false, false, false, false};
    std::vector<string> seeds;      // Output file
    std::ifstream ifs;              // Input File
    std::ofstream ofs("seeds.txt"); // Output File
    u16 stage = 4;                      // Stage ID
    u32 range;                      // Search Range
    clock_t start = clock();

    // Checking Arguments.
    if (argc < 3)
    {
        std::cout << "[usage] ./SeedHack WaveInfo Range [Stage]" << std::endl;
        std::cout << "[usage] ./SeedHack -r TEXTFILE []" << std::endl;
        return -1;
    }

    for (u16 i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-R"))
        {
            mMode[1] = true;
        }
        if (!strcmp(argv[i], "-r"))
        {
            // Load Seeds from text file.
            ifs.open(std::string(argv[i + 1]));
            if (ifs.fail())
            {
                std::cout << std::string(argv[i + 1]) + ", No such file on directory." << std::endl;
                return -1;
            }
            mMode[0] = true;
        }
    }
    if (!mMode[0])
    {
        try
        {
            wave = std::string(argv[1]); // Search Range
            range = std::atof(argv[2]);  // Search Range
        }
        catch (int error)
        {
            std::cout << "[usage] ./SeedHack WaveInfo Range [Stage]" << std::endl;
            std::cout << "[usage] ./SeedHack -r TEXTFILE []" << std::endl;
        }
    }

    cout << "Welcome Starlight SeedHack! Do no evil" << endl;
    cout << "Author       : tkgstrator" << endl;
    cout << "Reference    : shadowninja108, container12345" << endl;
    cout << "Threads      : " << threads << endl;
    cout << "Input Wave   : " << (mMode[0] ? "Unknown" : wave) << endl;
    cout << "Input Stage  : " << stage << endl;
    cout << "Search Range : " << (mMode[0] ? "Unknown" : std::to_string(range)) << endl;
    cout << "Regular Ex   : " << (mMode[1] ? "Enable" : "Disable") << endl;
    // cout << "Geyser  : " << (sflag ? "Enable" : "Disable") << endl;
    // cout << "Sequence: " << (gflag ? "Enable" : "Disable") << endl;
    cout << "Search Mode  : " << (mMode[0] ? "Sparse" : "Sequential") << endl;

    if (mMode[0]) // Sparse Mode
    {
        // #pragma omp parallel for
        std::string mSeed;
        for (; getline(ifs, mSeed);)
        {
            u32 seed = static_cast<unsigned int>(std::stol(mSeed, NULL, 0));
            Coop::Setting SH(seed, false);
            try
            {
                SH.getWaveInfo(wave);
                ostringstream sout;
                sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << SH.mSetting;
                Coop::Geyser GS(stage, seed);
                GS.getGeyser();
                if (regex_match(SH.mSetting, w13)) // Wave1 and Wave3
                    sout << "," << GS.mPosition[0] << "," << GS.mPosition[2];
                if (regex_match(SH.mSetting, w01)) // Wave1
                    sout << "," << GS.mPosition[0];
                if (regex_match(SH.mSetting, w02)) // Wave2
                    sout << "," << GS.mPosition[1];
                if (regex_match(SH.mSetting, w03)) // Wave3
                    sout << "," << GS.mPosition[2];
                seeds.push_back(sout.str());
            }
            catch (int error)
            {
            }
        }
    }
    else // Sequential Mode
    {
        // #pragma omp parallel for
        for (u32 seed = 0x0; seed < range; ++seed)
        {
            // if (seed % (range / 1000) == 0)
            // {
            //     std::cout << (double(seed) / double(range)) * 100 << "%" << std::endl;
            // }
            // Coop::Setting seedhack(seed);
            Coop::Setting SH(seed, true, true);
            try
            {
                SH.getWaveInfo(wave);
                ostringstream sout;
                sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << SH.mSetting;

                Coop::Geyser GS(stage, seed);
                GS.getGeyser();
                if (regex_match(wave, w13)) // Wave1 and Wave3
                    sout << "," << GS.mPosition[0] << "," << GS.mPosition[2];
                if (regex_match(wave, w01)) // Wave1
                    sout << "," << GS.mPosition[0];
                if (regex_match(wave, w02)) // Wave2
                    sout << "," << GS.mPosition[1];
                if (regex_match(wave, w03)) // Wave3
                    sout << "," << GS.mPosition[2];
                seeds.push_back(sout.str());
            }
            catch (int error)
            {
                // std::cout << "NOT MATCH" << std::endl;
            }
        }

        // ostringstream sout;
        // sout << "0x" << setw(8) << uppercase << setfill('0') << hex << seed << "," << dec << waveinfo;
        //     if (!rflag ? waveinfo == wave : regex_match(waveinfo, regex(wave)))
        //     {
        //         ostringstream sout;
        //         // std::vector<std::string> gpos = tkg.getGeyser(stage_id);
        //         if (sout.str() != "")
        //             seeds.push_back(sout.str());
        //     }
        // }
        // if (wave == waveinfo) {
        //     seeds.push_back(sout.str());
        // }
    }
    sort(seeds.begin(), seeds.end()); // Sorting
    for (auto val : seeds)            // Output
    {
        ofs << val << endl;
    }
    const double time = static_cast<double>(clock() - start) / CLOCKS_PER_SEC * 1000.0 / threads;
    cout << "Running time : " << time << "ms" << endl;
    return 0;
}