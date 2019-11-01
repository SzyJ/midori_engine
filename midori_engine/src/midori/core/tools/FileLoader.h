// Author: Szymon Jackiewicz
// 
// Project: midori_engine
// File: FileLoader.h
// Date: 01/11/2019

#pragma once

#include "midori/core/Log.h"

#include <fstream>
#include <string>

namespace midori {

    bool LoadFile(const char* from, std::string& into) {
        std::ifstream file;
        std::string temp;

        file.open(from);
        if (!file.is_open()) {
            return false;
        }

        while (std::getline(file, temp)) {
            into.append(temp + "\n");
        }

        file.close();
        return true;
    }

}
