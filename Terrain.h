//
// Created by musiek on 07.06.2021.
//

#ifndef MARSROVER_TERRAIN_H
#define MARSROVER_TERRAIN_H


#include "Model.h"
#include "HeightMap.h"

class Terrain {
public:
    Model model;

    glm::vec3 minVec;
    glm::vec3 maxVec;

    HeightMap* heightMap;

    Terrain(string path);

    virtual ~Terrain();

    virtual void draw(Shader &shader);

    HeightMap* getHeightMap();

};


#endif //MARSROVER_TERRAIN_H
