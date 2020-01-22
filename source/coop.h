#pragma once

#include "types.h"
#include <string>
#include <vector>
#include <utility>

namespace coop
{
class Seedhack
{
public:
    void init(u32);
    void set(u16);
    std::vector<std::string> getGeyser();
    std::string getWaveInfo();
    bool rflag;
    u16 size;
    u32 seed;
    
    struct Prob
    {
        u16 event[7] = {18, 1, 1, 1, 1, 1, 1};
        u16 tide[3] = {1, 3, 1};
    };

    struct Wave
    {
        u16 event[3] = {0, 0, 0};
        u16 tide[3] = {1, 1, 1};
    };

    struct Dam
    {
        bool reuse[5] = {true, true, true, true, true};
        u16 start[5] = {0, 1, 2, 3, 4};
        std::string goal[5][2] = {
            {"3", "3"},
            {"2", "3"},
            {"1", "1"},
            {"4", "1"},
            {"3", "2"}};
    };
    
    struct Toba
    {
        bool reuse[5] = {false, true, true, true, true};
        u16 start[5] = {0, 1, 2, 3, 4};
        std::string goal[5][2] = {
            {"3", "3"},
            {"2", "3"},
            {"4", "1"},
            {"4", "1"},
            {"2", "3"}};
    };
    
    struct Fune
    {
        bool reuse[4] = {true, false, true, true};
        u16 start[4] = {0, 1, 2, 3};
        std::string goal[4][2] = {
            {"A", "B"},
            {"C", "D"},
            {"E", "F"},
            {"G", "H"}};
    };

    struct Pola
    {
        bool reuse[4] = {false, false, false, false};
        u16 start[4] = {0, 1, 2, 3};
        u16 goal[4][1] = {
            {3},
            {2},
            {2},
            {3}};
    };

    struct Toki
    {
        bool reuse[5] = {true, true, true, true, true};
        u16 start[5] = {0, 1, 2, 3, 4};
        u16 goal[5][2] = {
            {4, 2},
            {3, 4},
            {0, 0},
            {1, 1},
            {1, 0}};
    };
};
}; // namespace coop