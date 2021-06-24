//
// Created by musiek on 07.06.2021.
//

#include <fstream>
#include <detail/type_vec2.hpp>
#include <iostream>
#include <cmath>
#include "HeightMap.h"

HeightMap::HeightMap(string path, glm::vec3 min, glm::vec3 max) {

    std::ifstream file(path, std::ios::binary);

    string format;
    file >> format;

    file >> pixelsWidth >> pixelsHeight;

    map = new uint*[pixelsWidth];
    for (int i = 0; i < pixelsWidth; i++) {
        map[i] = new uint[pixelsHeight];
    }

    int tmp1, tmp2, tmp3;

    uint maxVal;
    file >> maxVal;

    for (int x = 0; x < pixelsWidth; x++) {
        for (int y = 0; y < pixelsHeight; y++) {
            file >> tmp1;
            file >> tmp2;
            file >> tmp3;

            map[x][y] = (tmp1 + tmp2 + tmp3) / 3;

            if (firstRead) {
                minimumBrightness = map[x][y];
                maximumBrightness = map[x][y];
                firstRead = false;
            } else {
                if (minimumBrightness > map[x][y])
                    minimumBrightness = map[x][y];

                if (maximumBrightness < map[x][y])
                    maximumBrightness = map[x][y];
            }
        }
    }

    minVec = min;
    maxVec = max;

    size.x = abs(maxVec.x - minVec.x);
    size.y = abs(maxVec.y - minVec.y);
    size.z = abs(maxVec.z - minVec.z);
}

float HeightMap::getHeight(glm::vec2 pos) {
    glm::vec2 newPos = glm::vec2(-minVec.x, maxVec.z) - pos;

    float y = (float)(map[(int)round(newPos.y * this->pixelsHeight / size.z)][(int)round(newPos.x * this->pixelsWidth / size.x)] - this->minimumBrightness) / (float)(this->maximumBrightness - this->minimumBrightness);

    return y * (maxVec.y - minVec.y) + minVec.y;
}

HeightMap::~HeightMap() {
    delete[] map;

//    delete map;
}
