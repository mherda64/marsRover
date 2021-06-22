//
// Created by musiek on 07.06.2021.
//

#ifndef MARSROVER_HEIGHTMAP_H
#define MARSROVER_HEIGHTMAP_H

#include <string>
#include <vec3.hpp>

using namespace std;

class HeightMap {

public:
    uint** map;
    uint pixelsWidth;
    uint pixelsHeight;

    uint minimumBrightness;
    uint maximumBrightness;

    glm::vec3 minVec;
    glm::vec3 maxVec;

    glm::vec3 size;

    bool firstRead = true;

    HeightMap(string path, glm::vec3 min, glm::vec3 max);

    virtual ~HeightMap();

    float getHeight(glm::vec2 pos);


};


#endif //MARSROVER_HEIGHTMAP_H
