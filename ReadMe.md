# What's SeedHack
SeedHack is the best way to fix waves for Salmon Run in the Shoal. Please make sure the console applying SeedHack must be a host.

# How to use SeedHack

## 0.0.1
`SeedHack.exe WaveInfo(Int) Range(Int)`

## 0.1.0
`SeedHack.exe WaveInfo(RegExp) Range(Int) [Geyser Position(RegExp)]`

## WaveInfo
Wave: an integer number for waves combination.

| Event | High-Tide | Middle-Tide | Low-Tide |
| :---: | :---: | :---: | :---: |
| NoEvent | 20  | 10  | 00 |
| Rush | 21 | 11 | - |
| Goldie Seeking | 22  | 12 | - |
| The Griller | 23  | 13  | - |
| The Mothership | 24  | 14  | 04 |
| Fog | 25  | 15  | 05  |
| Cohock Charge | -  | -  | 06 |

If you want the waves(High-Tide Griller, Middle-Tide NoEvent, Low-Tide Fog), you input a number like as 231005

## Range

The range for search. If you input 100000 as range, this program searches the id to 100000 from 0.

## Geyser Position

I've resarched every stage within High-Tide.

| Event | High-Tide | Middle-Tide |
| :---: |:---:|:---:|
| Spawning Grounds | [0,1,2,3,4] | No Test |
| Marooner's Bay | [0,1,2,3] | No Test |
| Lost Outpost | [0,1,2,3,4]| No Test |
| Salmonid Smokeyard | [0,1,2,3,4] | No Test|
| Ruins of Ark Polaris | [0,1,2,3] | No Test |

### RegExp

```cpp
1111    // the string having the substring "1111". 
[01]{N} // the string having '0' or '1' which size is at least N.
[^2]{N} // the string not having '2' which size is at least N.

```

# For example 

`SeedHack.exe 201306 65535`

```
0x000029BA
0x0000342C
0x00003E95
0x00004A28
0x00004A45
0x00005D19
0x00005E6D
0x00006426
0x00007582
0x00008665
0x0000992F
0x0000A996
0x0000B558
0x0000B66F
0x0000BBF8
0x0000C1EE
0x0000CE53
0x0000EF52
0x0000F686
0x0000FE10
0x0000FF56
```

# Apply for IPSwitch

First, you must find the address for SeedHack.

| Ver | Address |
| --- |---|
| 3.1.0| 00208C74|
| 4.9.1| 0036B710 |
| 5.0.0 | 00363830 |
| 5.0.1 | 00376810 |
| 5.1.0 | 0036C0C0 |
| 5.2.0 | 003753B0 |
| 5.2.1 | 003753B0 |
| 5.2.2 | 003753B0 |
| 5.3.0 | 003753B0 |
| 5.3.1 | 00XXXXXX |
| 5.4.0 | 00XXXXXX |
| 5.5.0 | 00XXXXXX |

To prevent using online match making, I can't list the latest version's address. Search it by yourself or wait for release 5.5.1/5.6.0.

## Code
Convert ARM to HEX on [Online HEX to ARM Converter](http://armconverter.com/).

You input the ARM code like `MOV X0, #0x29BA`, then you also get `403785D2`.

```
// SeedHack 201306 [tkgling]
@disabled
00363830 403785D2
```

If you'd like to able to apply the HEX value grater than 0xFFFF, you must divide the code. For example, this program provide you the number `0x12345678`. 

```
MOV  X0, #0x12340000
MOVK X0, #0x5678
```

```
// SeedHack 201306 [tkgling]
@disabled
00363830 8046A2D2
00363834 00CF8AF2
```

# Special Thanks
* [container12345](https://twitter.com/container12345) reverse engineering
* [shadowninja108](https://github.com/shadowninja108) knowledgement
* [simontime](https://github.com/simontime) sead library

