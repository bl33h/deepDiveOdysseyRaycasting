/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: levels.h
@version: I
Creation: 06/07/2023
Last modification: 09/11/2023
*Some parts were made using the AIs Bard and ChatGPT
------------------------------------------------------------------------------*/

#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

struct Level {
    std::string mapFile;
    std::string name;
};

extern std::vector<Level> levels;

#endif
